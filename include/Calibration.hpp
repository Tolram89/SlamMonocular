#pragma once
#include "FrameData.hpp"
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @class Calibration
 * @brief Service responsible for estimating camera intrinsic parameters.
 *
 * Uses Zhang's calibration method based on a planar chessboard pattern.
 * Accumulates 2D-3D point correspondences across frames and computes
 * the camera intrinsic matrix (K) and distortion coefficients.
 */
class Calibration {
private:
    float squareSize;                                   ///< Physical size of a square on the chessboard (e.g., in meters).
    cv::Size patternSize;                               ///< Number of internal corners per board row and column (width, height).
    std::vector<std::vector<cv::Point2f>> imagePoints; ///< Detected 2D image coordinates of chessboard corners.
    std::vector<std::vector<cv::Point3f>> objectPoints;///< Known 3D physical coordinates of chessboard corners.

    cv::Size imageSize;     ///< Resolution of the processed image frames.
    bool isImageSizeSet;    ///< Flag indicating if image resolution has been locked.

public:
    /**
     * @brief Constructs a Calibration service.
     * @param squareSize Physical size of a single square edge.
     * @param patternSize Number of inner corners (width x height).
     * @throws std::invalid_argument If squareSize <= 0 or patternSize dimensions <= 0.
     */
    Calibration(float squareSize, cv::Size patternSize);

    /**
     * @brief Detects corners in a frame and stores valid point correspondences.
     * @param frame FrameData containing the input image.
     * @return true if the chessboard pattern was successfully detected, false otherwise.
     */
    [[nodiscard]] bool addFrame(const FrameData& frame);

    /**
     * @brief Gets the total number of valid frames accumulated for calibration.
     * @return Number of stored calibration frames.
     */
    [[nodiscard]] std::size_t getFrameCount() const;

    /**
     * @brief Solves camera intrinsic calibration and updates the Camera instance.
     * @param camera Reference to the Camera object where intrinsics will be written.
     * @return true if calibration succeeded with acceptable RMS error (< 1.0), false otherwise.
     */
    [[nodiscard]] bool calibrate(Camera& camera);
};