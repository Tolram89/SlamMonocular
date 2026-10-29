#pragma once
#include <opencv2/core/mat.hpp>
#include <string>

/**
 * @brief Camera optical model: intrinsic matrix K and distortion coefficients.
 *
 * A Camera instance is created empty (uncalibrated). Parameters are set and
 * validated via setIntrinsics() (directly or through loadIntrinsics()):
 * a Camera object is therefore either empty or fully valid.
 */
class Camera {
private:
	cv::Mat cameraMatrix;
	cv::Mat distCoeffs;

	/**
	 * @brief Validates and converts the camera matrix K to CV_64F.
	 * @param[in,out] K Matrix of size 3x3 (CV_32F or CV_64F, with fx > 0 and fy > 0).
	 * @return true if valid and converted; false otherwise.
	 */
	[[nodiscard]] bool validateAndConvertCameraMatrix(cv::Mat& K);

	/**
	 * @brief Validates and converts the distortion coefficients vector to CV_64F.
	 * @param[in,out] dist Matrix of size 1x5 or 5x1 (CV_32F or CV_64F).
	 * @return true if valid and converted; false otherwise.
	 */
	[[nodiscard]] bool validateAndConvertDistCoeffs(cv::Mat& dist);

public:
	/**
	 * @brief Sets both the intrinsic matrix and distortion coefficients.
	 *
	 * Rules: neither matrix can be empty; @p k must be 3x3 with fx > 0 and fy > 0;
	 * @p dist must be 1x5 or 5x1. Both matrices must be of type CV_64F or CV_32F
	 * (CV_32F matrices are automatically converted to CV_64F).
	 *
	 * @param k    Intrinsic matrix.
	 * @param dist Distortion coefficients.
	 * @return true if both parameters are accepted and stored; false otherwise,
	 *         leaving the camera state unchanged.
	 */
	[[nodiscard]] bool setIntrinsics(const cv::Mat& k, const cv::Mat& dist);

	/**
	 * @brief Checks whether the camera has valid calibration parameters.
	 * @return true if matrices are populated (and thus validated by setIntrinsics());
	 *         false for an empty camera.
	 */
	bool isCalibrated() const;

	/**
	 * @brief Loads parameters from an OpenCV file (YAML/XML) containing
	 *        "cameraMatrix" and "distCoeffs" keys.
	 *
	 * Read values pass through setIntrinsics() and adhere to the same validation rules.
	 *
	 * @param fileName Path to the input file.
	 * @return true if the file is read and its values accepted; false if unreadable,
	 *         if a key is missing, or if values are rejected. Leaves state unchanged on failure.
	 */
	[[nodiscard]] bool loadIntrinsics(const std::string& fileName);

	/**
	 * @brief Saves parameters to an OpenCV file (using the same keys as loadIntrinsics()).
	 * @param fileName Path to the output file (overwritten if it exists).
	 * @return true if writing succeeds; false if the camera is uncalibrated
	 *         (no file created) or if the file cannot be opened for writing.
	 */
	[[nodiscard]] bool saveIntrinsics(const std::string& fileName) const;

	/** @brief Copy of the intrinsic matrix (3x3, CV_64F), empty if uncalibrated. */
	cv::Mat getCameraMatrix() const;

	/** @brief Copy of the distortion coefficients (1x5 or 5x1, CV_64F), empty if uncalibrated. */
	cv::Mat getDistCoeffs() const;
};