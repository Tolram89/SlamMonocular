#pragma once
#include "FrameData.hpp"

class Calibration {
private:
	float squareSize;
	cv::Size patternSize;
	std::vector < std::vector<cv::Point2f>> imagePoints;
	std::vector < std::vector<cv::Point3f>> objectPoints;

	cv::Size imageSize;
	bool isImageSizeSet = false;

public:
	Calibration(float squareSize, cv::Size patternSize);
	[[nodiscard]] bool addFrame(const FrameData& frame);
	std::size_t getFrameCount() const;
	[[nodiscard]] bool calibrate(Camera& camera);

};
