#pragma once
#include "Camera.hpp"
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @struct FrameData
 * @brief Data Transfer Object (DTO) holding data associated with a single video frame.
 *
 * Transport structure containing raw image, extracted 2D keypoints,
 * ORB descriptors, estimated SE(3) pose matrix, and 2D-2D matches.
 */
struct FrameData {
    int id;                                       ///< Unique frame sequential identifier.
    cv::Mat image;                                ///< Raw or preprocessed image frame.
    std::vector<cv::KeyPoint> keypoints;          ///< Extracted 2D interest points.
    cv::Mat descriptors;                          ///< ORB feature descriptors.
    cv::Mat pose;                                 ///< 4x4 camera pose matrix SE(3).
    std::vector<cv::DMatch> matches;              ///< Feature matches with previous frame.
    std::shared_ptr<const Camera> camera;         ///< Shared immutable reference to sensor model.

    /**
     * @brief Constructs a FrameData instance.
     * @param id Sequential frame index.
     * @param image Input BGR or grayscale image matrix.
     * @param camera Shared reference to the camera model.
     */
    FrameData(int id, cv::Mat image, std::shared_ptr<const Camera> camera);
};