#pragma once
#include <opencv2/core/mat.hpp>

class Camera {
private:
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;
public:

	void setIntrinsics(const cv::Mat& cameramatrix, const cv::Mat& distCoeffs);
	bool isCalibrated() const;
	bool loadIntrinsics(const std::string& fileName);
	bool saveintrinsics(const std::string& fileName);
	const cv::Mat& getCameramatrix() const;
	const cv::Mat& getDistCoeffs() const;
};