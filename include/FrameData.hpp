# pragma once
#include <opencv2/core/mat.hpp>
#include <memory>
#include <vector>
#include "Camera.hpp"

struct FrameData {

	int id;
	cv::Mat image;
	std::vector<cv::KeyPoint> keyPoints;
	cv::Mat descriptors;
	cv::Mat pose;
	std::vector<cv::DMatch> matches;
	std::shared_ptr<const Camera> camera;


	FrameData(int id, const cv::Mat& image, std::shared_ptr<const Camera> camera);


};