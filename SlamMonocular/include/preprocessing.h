#pragma once
#include <opencv2/opencv.hpp>

struct CameraConfig {
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
	
};

CameraConfig readParameter();