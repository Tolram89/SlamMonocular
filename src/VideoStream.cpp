#include "../include/VideoStream.hpp"

VideoStream::VideoStream(const std::string& path)
	:videoCapture(cv::VideoCapture(path))
{
	if(!isOpened())
		throw std::runtime_error("Couldn't open the file");
}

VideoStream::VideoStream(int deviceId)
	:videoCapture(cv::VideoCapture(deviceId))
{
	if (!isOpened())
		throw std::runtime_error("Couldn't open the file");
}

bool VideoStream::read(cv::Mat& out)
{
	videoCapture.read(out);
	return !out.empty();
}

bool VideoStream::isOpened() const
{
	return videoCapture.isOpened();

}
