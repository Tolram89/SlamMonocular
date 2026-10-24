#pragma once
#include <opencv2/videoio.hpp>

class VideoStream {
private:
	cv::VideoCapture videoCapture;
public:
	VideoStream(const std::string& path);
	VideoStream(int deviceId);

	bool read(cv::Mat& out);
	bool isOpened();
};