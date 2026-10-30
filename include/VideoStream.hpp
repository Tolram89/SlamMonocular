#pragma once
#include <opencv2/videoio.hpp>

class VideoStream {
private:
	cv::VideoCapture videoCapture;
public:
	VideoStream(const std::string& path);
	VideoStream(int deviceId);

	[[nodiscard]] bool read(cv::Mat& out);
	[[nodiscard]] bool isOpened() const;
};