# Architecture Decision Records (ADR) — SlamMonocular

Ce document répertorie les décisions d'architecture majeures et les choix de conception logicielle retenus pour le projet de SLAM monoculaire.

---

## ADR 001 : Séparation entre `Camera` et `Calibration`

* **Statut :** Accepté
* **Contexte :** La calibration d'une caméra produit une matrice intrinsèque $K$ et des coefficients de distorsion $D$. Il faut décider où résident ces données et quel composant effectue l'estimation.
* **Décision :** 
  * `Camera` est le **modèle d'état géométrique immuable** : il stocke les matrices $K$ et $D$ et gère leur persistance (chargement/sauvegarde YAML).
  * `Calibration` est un **service d'estimation temporaire** : son unique rôle est de détecter les damiers, d'accumuler les correspondances 2D-3D et de calculer $K$ et $D$ via la méthode de Zhang pour initialiser un objet `Camera`.
* **Justification (SRP) :** Séparer le stockage du modèle optique du service de calcul permet de respecter le principe de responsabilité unique (Single Responsibility Principle) et d'injecter facilement l'objet `Camera` sous forme de pointeur partagé (`std::shared_ptr<const Camera>`) dans le pipeline sans dépendre de l'outil de calibration.

---

## ADR 002 : Patron DTO (Data Transfer Object) pour `FrameData`

* **Statut :** Accepté
* **Contexte :** Une image au cours du pipeline SLAM est enrichie progressivement (points d'intérêt, descripteurs ORB, pose géométrique, appariements).
* **Décision :** `FrameData` est conçue comme une structure/classe de données passive (DTO/POD). Elle ne contient aucune méthode de traitement algorithmique.
* **Justification :** 
  * Isolation stricte entre les **données** (`FrameData`) et les **traitements** (`Preprocessing`, `InterestPointExtractor`, `Tracking`, `Mapping`).
  * Facilite le passage de données entre les différents modules et améliore la testabilité unitaire des services.

---

## ADR 003 : Exclusion de l'action `PAUSE` en V1

* **Statut :** Accepté
* **Contexte :** Une mise en pause de l'acquisition vidéo a été envisagée pour l'interface utilisateur.
* **Décision :** L'action `PAUSE` est exclue des fonctionnalités de la version 1 du système.
* **Justification :** 
  * Le SLAM monoculaire séquentiel repose sur l'hypothèse de **continuité spatio-temporelle** entre deux images successives $F_{t-1}$ et $F_t$ pour estimer la pose relative.
  * Si l'utilisateur déplace la caméra pendant une pause, la reprise du flux vidéo provoque un saut spatial rompant la continuité, entraînant un échec d'appariement des descripteurs et une perte de suivi (*tracking loss*).
  * En l'absence d'un module de relocalisation complet (type Bag-of-Words / BoW), interdire la pause garantit la robustesse du suivi géométrique.

---

## ADR 004 : Découplage Vue-Contrôleur via `UserAction` et dépouillement centralisé

* **Statut :** Accepté
* **Contexte :** Interception des entrées utilisateur (clavier/souris) pour piloter le système SLAM (démarrage, calibration, arrêt).
* **Décision :** 
  * Définition d'une énumération d'intents abstraits `UserAction`.
  * La Vue (`ControlPanel`) effectue l'unique appel à `cv::pollKey()` par frame et met à jour l'état synchrone des objets `Button`.
* **Justification :** 
  * Évite la perte d'événements dans la file de messages du système d'exploitation (*OS event pump*) causée par des appels multiples dispersés.
  * Garantit l'absence de dépendance directe du Contrôleur envers l'API graphique sous-jacente (OpenCV HighGUI).
