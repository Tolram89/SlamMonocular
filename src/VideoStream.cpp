#include "../include/VideoStream.hpp"

VideoStream::VideoStream(const std::string& path)
	:videoCapture(cv::VideoCapture(path))
{
	if(!isOpened())
		std::runtime_error("Couldn't open the file");
}

VideoStream::VideoStream(int deviceId)
	:videoCapture(cv::VideoCapture(deviceId))
{
	if (!isOpened())
		std::runtime_error("Couldn't open the file");
}

bool VideoStream::read(cv::Mat& out)
{
	videoCapture.read(out);
	if (out.empty())
		return false;
	return true;
}

bool VideoStream::isOpened() const
{
	if(!videoCapture.isOpened())
		return false;
	return true;
}
