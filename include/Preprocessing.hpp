#pragma once
#include <opencv2/core/mat.hpp>
#include "FrameData.hpp"

class Preprocessing {
private: 
	cv::Mat mapX;
	cv::Mat mapY;
public:
	Preprocessing(const Camera& camera, cv::Size size);
	void undistort(const FrameData& frame);

};