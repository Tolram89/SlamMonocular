find_package(GTest CONFIG REQUIRED)
include(GoogleTest)


#test pour Camera
add_executable(camera_tests test_camera.cpp)
target_link_libraries(camera_tests PRIVATE slam_core GTest::gtest_main)
gtest_discover_tests(camera_tests)

#test pour VideoStream
add_executable(videoStream_tests test_videoStream.cpp)
target_link_libraries(videoStream_tests PRIVATE slam_core GTest::gtest_main)
gtest_discover_tests(videoStream_tests)

#test pour Calibration
add_executable(calibration_tests test_calibration.cpp)
target_link_libraries(calibration_tests PRIVATE slam_core GTest::gtest_main)
gtest_discover_tests(calibration_tests)
target_compile_definitions(calibration_tests PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/")

