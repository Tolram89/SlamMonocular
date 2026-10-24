cmake_minimum_required(VERSION 3.20)

# Spécifier le toolchain vcpkg à CMake
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(SlamMonocular CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(SlamMonocular ${SOURCES}   "src/SlamSystem.cpp" "src/Camera.cpp" "src/VideoStream.cpp" "src/FrameData.cpp" "src/Preprocessing.cpp" "src/InterestPoint.cpp" "src/Tracking.cpp" "src/Mapping.cpp" "src/Calibration.cpp" "src/UserInterface.cpp" "src/VideoWindow.cpp" "src/MapWindow.cpp" "src/ControlPanel.cpp" "src/Button.cpp")

target_include_directories(SlamMonocular PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(SlamMonocular PRIVATE ${OpenCV_LIBS})