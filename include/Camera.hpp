#pragma once
#include <opencv2/core/mat.hpp>

class Camera {
private:
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
};