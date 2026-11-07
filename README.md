# Monocular SLAM System (C++)

A modular, real-time sequential Monocular Visual SLAM (Simultaneous Localization and Mapping) implementation written in C++ using OpenCV and GoogleTest.

This project focuses on clean software engineering principles, strict separation of concerns via the Model-View-Controller (MVC) pattern, Single Responsibility Principle (SRP), and thorough unit testing.

---

## 🛠 Features & Architecture

* **Modular Architecture (MVC):**
  * **Model:** Handles optical sensor modeling (`Camera`), calibration (`Calibration`), video ingestion (`VideoStream`), frame DTOs (`FrameData`), feature extraction, tracking, and mapping.
  * **View:** Manages user interaction and UI elements (`UserInterface`, `ControlPanel`, `VideoWindow`, `MapWindow`) decoupled via an abstract `UserAction` event system.
  * **Controller:** Coordinates pipeline execution flow (`SlamSystem`).
* **Sensor Calibration:** Integrated camera calibration using Zhang's method with planar chessboard patterns.
* **Robust Data Transfer Objects (DTO):** `FrameData` encapsulates single-frame observations (2D keypoints, ORB descriptors, pose matrices) without mixing processing logic.
* **Unit Tested:** Core modules are validated using GoogleTest (`GTest`).
* **Documented:** Fully documented API headers compatible with Doxygen.

---

## 📋 Prerequisites

* **C++ Compiler:** Supporting C++17 or C++20 (GCC, Clang, or MSVC).
* **CMake:** Version 3.15 or higher.
* **OpenCV:** Version 4.x (Core, HighGUI, ImgProc, Calib3d, Features2d).
* **GoogleTest:** Required for running the test suite (managed via `vcpkg` or system installation).

---

## 🚀 Building the Project

### 1. Clone the repository
```bash
git clone https://github.com/your-username/slam-monocular.git
cd slam-monocular
```

### 2. Configure with CMake
If using `vcpkg` for dependency management:
```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```

Standard build:
```bash
cmake -B build -S .
```

### 3. Build the executables
```bash
cmake --build build --config Release
```

---

## 🧪 Running Unit Tests

To execute the unit test suite built with GoogleTest:

```bash
cd build
ctest --output-on-failure
```

Or run the test binary directly:
```bash
./bin/slam_tests
```

---

## 🎮 Controls & Keyboard Shortcuts

Interactions are processed synchronously by the `ControlPanel` component using non-blocking keyboard polling:

| Key | Action | Description |
| :---: | :---: | :--- |
| `S` / `s` | `START` | Starts the SLAM tracking and mapping pipeline. |
| `C` / `c` | `CALIBRATE` | Triggers corner detection and calibration procedure. |
| `Q` / `q` / `Esc` | `QUIT` | Gracefully closes windows and exits the application. |

*Note: The `PAUSE` action is intentionally disabled in V1 to preserve spatiotemporal continuity and prevent tracking loss.*

---

## 📚 Generating API Documentation

The source headers contain inline Doxygen annotations. To build the HTML documentation:

```bash
doxygen Doxyfile
```

The generated documentation will be available in `docs/html/index.html`.

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.
