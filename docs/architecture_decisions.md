# Architecture Decision Records (ADR) — SlamMonocular

This document lists the key architectural decisions and software design choices made for the monocular SLAM system project.

---

## ADR 001: Separation of `Camera` and `Calibration`

* **Status:** Accepted
* **Context:** Camera calibration yields an intrinsic camera matrix $K$ and distortion coefficients $D$. We need to decide where this state resides and which component performs the estimation.
* **Decision:** 
  * `Camera` is the **immutable geometric state model**: it stores matrices $K$ and $D$ and manages their persistence (YAML loading/saving).
  * `Calibration` is a **temporary estimation service**: its sole responsibility is to detect chessboard patterns, accumulate 2D-3D point correspondences, and compute $K$ and $D$ using Zhang's method to initialize a `Camera` instance.
* **Rationale (SRP):** Separating the optical model storage from the calculation service satisfies the Single Responsibility Principle (SRP) and allows injecting the `Camera` object as a shared pointer (`std::shared_ptr<const Camera>`) throughout the pipeline without depending on calibration tools.

---

## ADR 002: Data Transfer Object (DTO) Pattern for `FrameData`

* **Status:** Accepted
* **Context:** An image frame is progressively enriched throughout the SLAM pipeline (2D keypoints, ORB descriptors, geometric camera pose, feature matches).
* **Decision:** `FrameData` is designed as a passive data structure/class (DTO/POD). It contains no algorithmic processing logic.
* **Rationale:** 
  * Strict isolation between **data** (`FrameData`) and **processing services** (`Preprocessing`, `InterestPointExtractor`, `Tracking`, `Mapping`).
  * Facilitates data passing across modules and improves unit testability of individual services.

---

## ADR 003: Exclusion of `PAUSE` Action in V1

* **Status:** Accepted
* **Context:** Pausing video acquisition was considered for the user interface.
* **Decision:** The `PAUSE` action is excluded from the version 1 system scope.
* **Rationale:** 
  * Sequential monocular SLAM relies on the **spatiotemporal continuity assumption** between successive images $F_{t-1}$ and $F_t$ to estimate relative camera pose.
  * Moving the camera while paused causes a spatial jump upon resumption, leading to descriptor matching failure and tracking loss.
  * Without a full place-recognition / relocalization module (e.g., Bag-of-Words / BoW), disallowing pause ensures robust geometric tracking.

---

## ADR 004: View-Controller Decoupling via `UserAction` and Centralized Polling

* **Status:** Accepted
* **Context:** Intercepting user inputs (keyboard/mouse) to drive the SLAM system (start, calibration, quit).
* **Decision:** 
  * Define an abstract intent enumeration `UserAction`.
  * The View (`ControlPanel`) performs a single `cv::pollKey()` call per frame and updates the synchronous state of `Button` objects.
* **Rationale:** 
  * Prevents event loss in the operating system's event queue caused by scattered multiple key-polling calls.
  * Guarantees zero direct dependency from the Controller onto the underlying GUI framework (OpenCV HighGUI).
