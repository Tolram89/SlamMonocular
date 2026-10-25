# pragma once
#include <opencv2/core/mat.hpp>
#include "Camera.hpp"

class FrameData {
private:
	int id;
	cv::Mat image;
	std::vector<cv::KeyPoint> keyPoints;
	cv::Mat descriptors;
	cv::Mat pose;
	std::vector<cv::DMatch> matches;
	std::shared_ptr<Camera> camera;

public:
	FrameData(int id, const cv::Mat& image, std::vector<cv::KeyPoint> keyPoints);


};