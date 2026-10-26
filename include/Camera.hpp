#pragma once
#include <opencv2/core/mat.hpp>

class Camera {
private:
	cv::Mat cameraMatrix=cv::Mat();
	cv::Mat distCoeffs=cv::Mat();
public:

	void setIntrinsics(const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs);
	bool isCalibrated() const;
	bool loadIntrinsics(const std::string& fileName);
	bool saveIntrinsics(const std::string& fileName);
	const cv::Mat& getCameramatrix() const;
	const cv::Mat& getDistCoeffs() const;
};