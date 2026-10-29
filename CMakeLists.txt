cmake_minimum_required(VERSION 3.20)
project(SlamMonocular CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_library(slam_core STATIC
    src/Button.cpp src/Calibration.cpp src/Camera.cpp src/ControlPanel.cpp
    src/FrameData.cpp src/InterestPoints.cpp src/Mapping.cpp src/MapWindow.cpp
    src/Preprocessing.cpp src/SlamSystem.cpp src/Tracking.cpp
    src/UserInterface.cpp src/VideoStream.cpp src/VideoWindow.cpp)
target_include_directories(slam_core PUBLIC include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(slam_core PUBLIC ${OpenCV_LIBS})

add_executable(SlamMonocular src/main.cpp)
target_link_libraries(SlamMonocular PRIVATE slam_core)


set(CONFIG_SOURCE "${CMAKE_SOURCE_DIR}/config")
set(CONFIG_DEST "$<TARGET_FILE_DIR:SlamMonocular>/config")

add_custom_command(TARGET SlamMonocular POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CONFIG_DEST}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CONFIG_SOURCE}/calibration.yaml"
            "${CONFIG_DEST}/calibration.yaml"
    COMMENT "Initialisation de la configuration si nécessaire"
)
enable_testing()
add_subdirectory(tests)