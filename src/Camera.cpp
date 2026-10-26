#include "../include/Camera.hpp"
#include <opencv2/core/persistence.hpp>
#include <iostream>

void Camera::setIntrinsics(const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs)
{
	if (cameraMatrix.size() == cv::Size(3, 3) &&
		(distCoeffs.size() == cv::Size(1, 5) ||
		distCoeffs.size() == cv::Size(5, 1)))
	{
		this->cameraMatrix = cameraMatrix.clone();
		this->distCoeffs = distCoeffs.clone();
	}
	
}

bool Camera::isCalibrated() const
{
	if(cameraMatrix.empty() || distCoeffs.empty())
		return false;
	if (!(cameraMatrix.size() == cv::Size(3, 3) ||
		distCoeffs.size() == cv::Size(1, 5) ||
		distCoeffs.size() == cv::Size(5, 1))) {
		return false;
	}
	if(cameraMatrix.at<double>(0, 0) <= 0 || cameraMatrix.at<double>(1, 1)<=0)
		return false;
	return true;
}

bool Camera::loadIntrinsics(const std::string& fileName)
{
	cv::FileStorage fs(fileName, cv::FileStorage::READ);
	if (!fs.isOpened()) {
		throw std::runtime_error("Cannot open file for reading : " + fileName);
	}
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;
	fs.release();
	return true;
}

bool Camera::saveIntrinsics(const std::string& fileName)
{
	cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
	if (!fs.isOpened()) {
		throw std::runtime_error("Cannot open for writing : " + fileName);
	}
	fs << "cameraMatrix" <<  cameraMatrix;
	fs << "distCoeffs" << distCoeffs;
	fs.release();
	fs.release();

	return true;
}

const cv::Mat& Camera::getCameramatrix() const
{
	return this->cameraMatrix;
}

const cv::Mat& Camera::getDistCoeffs() const
{
	return this->distCoeffs;
}
