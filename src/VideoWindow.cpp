#include "../include/VideoWindow.hpp"

VideoWindow::VideoWindow(const std::string& title)
	:title(title)
{
	cv::namedWindow(this->title);
}

void VideoWindow::show(const FrameData& frame) const
{
	frame.image.copyTo(displayBuffer);
	cv::drawKeypoints(displayBuffer, frame.keypoints, displayBuffer);
	std::string text = "[S/s] Start | [C/c] Calibrate | [Q/q/Esc] Quit";
	int font = cv::FONT_HERSHEY_PLAIN;
	cv::Point position(20, 460);
	double scale = 1.0;

	cv::putText(displayBuffer, text, position, font, scale, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
	cv::putText(displayBuffer, text, position, font, scale, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
	
	cv::imshow(this->title, displayBuffer);
}

void VideoWindow::close()
{
	cv::destroyWindow(this->title);
}
