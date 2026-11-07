#pragma once
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @class VideoStream
 * @brief RAII wrapper for video frame acquisition from hardware or files.
 * 
 * Encapsulates OpenCV cv::VideoCapture for single-frame reading.
 */
class VideoStream {
private:
    cv::VideoCapture capture; ///< Underlying OpenCV capture backend.

public:
    /**
     * @brief Opens a video file stream.
     * @param path File path to the video asset.
     * @throws std::runtime_error If the file stream fails to open.
     */
    explicit VideoStream(const std::string& path);

    /**
     * @brief Opens a hardware camera device stream.
     * @param deviceId Camera index (e.g., 0 for default webcam).
     * @throws std::runtime_error If the hardware device fails to open.
     */
    explicit VideoStream(int deviceId);

    /**
     * @brief Reads the next frame from the video stream.
     * @param[out] out Destination image matrix.
     * @return true if a frame was successfully read, false on end-of-stream or error.
     */
    bool read(cv::Mat& out);

    /**
     * @brief Checks if the capture stream is currently open and valid.
     * @return true if stream is opened.
     */
    [[nodiscard]] bool isOpened() const;
};