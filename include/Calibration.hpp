#pragma once
#include "FrameData.hpp"

class Calibration {
private:
	float squareSize;
	cv::Size patternSize;
	std::vector < std::vector<cv::Point2f>> imagepoints;
	std::vector < std::vector<cv::Point3f>> objectPoints;

public:
	Calibration(float squareSize, cv::Size patternSize);
	bool addFrame(const FrameData& frame);
	std::size_t getFrameCount() const;
	bool calibrate(Camera& camera);

};