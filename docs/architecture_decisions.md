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
## ADR 004: Direct Key Mapping via `UserAction` without `Button` Abstraction

* **Status:** Accepted (Revised)
* **Context:** Intercepting user keyboard inputs to drive the SLAM pipeline states (START, CALIBRATE, QUIT). We initially considered an intermediate `Button` UI component to maintain state.
* **Decision:** 
  * Remove the intermediate `Button` state class.
  * `ControlPanel` performs a single non-blocking `cv::pollKey()` call per frame and maps keycodes directly to the `UserAction` enumeration.
* **Rationale:** 
  * **YAGNI (You Ain't Gonna Need It):** In a real-time SLAM system, keyboard shortcuts provide optimal reactivity. Managing intermediate button state (`pressed = true/false`) within a single frame introduced unnecessary overhead and artificial complexity.
  * **Performance & Simplicity:** Direct keycode translation avoids string comparisons and dynamic allocations while retaining zero dependency between the Controller and OpenCV HighGUI.

---
  ## ADR 005: Introduction of `DoubleFrameData` for Temporal Pair Processing

* **Status:** Accepted
* **Context:** Sequential visual odometry (`Tracking`) and triangulation (`Mapping`) require a pair of consecutive frames $(F_{t-1}, F_t)$. Passing two separate `FrameData` objects complicates method signatures, leaves the initial frame ($t = 0$) without a valid predecessor, and mixes single-frame state with pairwise geometric relations.
* **Decision:**
  * Introduce `DoubleFrameData` to encapsulate a consecutive pair of shared frame pointers (`std::shared_ptr<FrameData> previous` and `current`), their feature correspondences (`std::vector<cv::DMatch> matches`), and the incremental camera motion (`cv::Mat relativePose`).
  * Keep single-frame attributes (`id`, `image`, `keypoints`, `descriptors`, and cumulative `globalPose`) inside `FrameData`.
  * Instantiate `DoubleFrameData` inside `SlamSystem` only once at least two frames have been acquired ($t \ge 1$).
* **Rationale:**
  * **Boundary Condition Safety:** Eliminates special-case branching for the first frame ($t = 0$) in `Tracking` and `Mapping`.
  * **Semantic & Memory Clarity:** Separates pairwise epipolar entities (`matches`, relative transform $T_{t-1 \rightarrow t}$) from absolute frame state ($T_{0 \rightarrow t}$), while avoiding deep copies of `std::vector<cv::KeyPoint>` via `std::shared_ptr`.