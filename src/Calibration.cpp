#include "../include/Calibration.hpp"
#include <stdexcept>
#include <opencv2/opencv.hpp>

Calibration::Calibration(float squareSize, cv::Size patternSize)
	:squareSize(squareSize), patternSize(patternSize), imageSize(0,0)
{

	if (patternSize.width <= 0 || patternSize.height <= 0)
		throw std::invalid_argument("patternSize width and height must be strictly greater than 0");
	if (squareSize <= 0)
		throw std::invalid_argument("squareSize must be strictly greater than 0");
}

bool Calibration::addFrame(const FrameData& frame)
{
	cv::Mat gray;
	std::vector<cv::Point2f> cornerBuf;
	cv::Mat img = frame.image;
	cv::cvtColor(frame.image, gray, cv::COLOR_BGR2GRAY);

	if (!isImageSizeSet) {
		imageSize = gray.size(); 
		isImageSizeSet = true;
	}
	else if (gray.size() != imageSize) {
		return false;
	}

	std::vector<cv::Point3f> objP;
	for (int i = 0; i < patternSize.height; i++) {
		for (int j = 0; j < patternSize.width; j++) {
			objP.push_back(cv::Point3f(j * squareSize, i * squareSize, 0.0f));
		}
	}

	bool found = cv::findChessboardCorners(gray, patternSize, cornerBuf, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE);

	if (found) {
		cv::cornerSubPix(gray, cornerBuf, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
		objectPoints.push_back(objP);
		imagePoints.push_back(cornerBuf);
	}
	return found;
}

std::size_t Calibration::getFrameCount() const
{
	return imagePoints.size();
}

bool Calibration::calibrate(Camera& camera)
{
	if (imagePoints.size() < 20) {
		return false;
	}

	cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat distCoeffs = cv::Mat::zeros(8, 1, CV_64F);
	std::vector<cv::Mat> rvecs, tvecs;

	double rms = cv::calibrateCamera(objectPoints, imagePoints, imageSize,
		cameraMatrix, distCoeffs, rvecs, tvecs);
	if (rms < 1.0) {
		return camera.setIntrinsics(cameraMatrix, distCoeffs);
	}
	return false;
}
