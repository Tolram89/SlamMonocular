#include "../include/Camera.hpp"

Camera::Camera()
{
	//TODO
}

void Camera::setIntrinsics(const cv::Mat& cameramatrix, const cv::Mat& distCoeffs)
{
	//TODO
}

bool Camera::isCalibrated() const
{
	//TODO
	return false;
}

bool Camera::loadIntrinsics(const std::string& fileName)
{
	//TODO
	return false;
}

bool Camera::saveintrinsics(const std::string& fileName)
{
	//TODO
	return false;
}

const cv::Mat& Camera::getCameramatrix() const
{
	// TODO: insérer une instruction return ici
	return this->cameraMatrix;
}

const cv::Mat& Camera::getDistCoeffs() const
{
	// TODO: insérer une instruction return ici
	return this->distCoeffs;
}
