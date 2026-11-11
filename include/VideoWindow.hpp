#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include "FrameData.hpp"

/**
 * @file VideoWindow.hpp
 * @brief Header file for the VideoWindow class.
 */

 /**
  * @class VideoWindow
  * @brief Manages the graphical display of the live video stream and 2D SLAM overlays.
  *
  * The VideoWindow class encapsulates an OpenCV HighGUI window to render processed frames,
  * detected 2D keypoints, and a Head-Up Display (HUD) showing available keyboard shortcuts.
  * It uses an internal reusable display buffer to avoid dynamic memory reallocations per frame
  * while preserving the immutability of the input FrameData.
  */
class VideoWindow {
private:
    std::string title;              ///< Title and unique identifier of the OpenCV window.
    mutable cv::Mat displayBuffer;  ///< Internal reusable buffer used for non-destructive rendering.

public:
    /**
     * @brief Constructs a new VideoWindow and initializes the underlying OS window.
     *
     * @param title The display title of the window.
     */
    VideoWindow(const std::string& title);

    /**
     * @brief Renders a processed frame with its 2D keypoints and HUD overlay.
     *
     * Copies the source image into the internal display buffer, draws detected keypoints,
     * overlays keyboard control instructions, and updates the window display.
     *
     * @param frame The immutable FrameData structure containing the image and keypoints to render.
     */
    void show(const FrameData& frame) const;

    /**
     * @brief Closes the window and releases associated HighGUI resources.
     */
    void close();
};