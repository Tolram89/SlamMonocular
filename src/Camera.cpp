#include "Camera.hpp"
#include <opencv2/core/persistence.hpp>


bool Camera::validateAndConvertCameraMatrix(cv::Mat& K)
{
	if (K.empty())
		return false;
	if (K.size() != cv::Size(3, 3))
		return false;
	if (K.type() == CV_64F)
	{
		if (K.at<double>(0, 0) <= 0 || K.at<double>(1, 1) <= 0)
			return false;
		return true;
	}
	else if (K.type() == CV_32F)
	{
		if (K.at<float>(0, 0) <= 0 || K.at<float>(1, 1) <= 0)
		{
			return false;
		}
		else {
			K.convertTo(K, CV_64F);
			return true;
		}
	}

	return false;


}

bool Camera::validateAndConvertDistCoeffs(cv::Mat& dist)
{
	if (dist.empty())
		return false;
	if (dist.size() != cv::Size(1, 5) && dist.size() != cv::Size(5, 1))
		return false;
	if (dist.type() == CV_64F)
	{
		return true;
	}
	else if (dist.type() == CV_32F)
	{
		dist.convertTo(dist, CV_64F);
		return true;
		
	}

	return false;
}

bool Camera::setIntrinsics(const cv::Mat& K, const cv::Mat& dist)
{
	cv::Mat K_temp = K.clone();
	cv::Mat dist_temp = dist.clone();
	if (validateAndConvertCameraMatrix(K_temp) && validateAndConvertDistCoeffs(dist_temp))
	{
		this->cameraMatrix = K_temp;
		this->distCoeffs = dist_temp;
		return true;
	}
	else {
		return false;
	}
}


bool Camera::isCalibrated() const
{
	if(cameraMatrix.empty() || distCoeffs.empty())
		return false;
	
	return true;
}

bool Camera::loadIntrinsics(const std::string& fileName)
{
	cv::FileStorage fs(fileName, cv::FileStorage::READ);
	if (!fs.isOpened()) {
		return false;
	}
	cv::Mat temp_camera_matrix;
	cv::Mat temp_dist_coeffs;
	fs["cameraMatrix"] >> temp_camera_matrix;
	fs["distCoeffs"] >> temp_dist_coeffs;

	return setIntrinsics(temp_camera_matrix, temp_dist_coeffs);
	
	
}

bool Camera::saveIntrinsics(const std::string& fileName) const
{
	if(this->isCalibrated())
	{
		cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
		if (!fs.isOpened()) {
			return false;
		}
		fs << "cameraMatrix" << cameraMatrix;
		fs << "distCoeffs" << distCoeffs;
		fs.release();

		return true;
	}
	return false;
}

cv::Mat Camera::getCameraMatrix() const
{
	return this->cameraMatrix.clone();
}

cv::Mat Camera::getDistCoeffs() const
{
	return this->distCoeffs.clone();
}
