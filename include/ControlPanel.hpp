#pragma once
#include "UserAction.hpp"

/**
 * @file ControlPanel.hpp
 * @brief Header file for the ControlPanel class.
 */

 /**
  * @class ControlPanel
  * @brief Handles user input interception and maps keyboard events to UserAction intents.
  *
  * The ControlPanel component executes non-blocking keyboard polling per frame via OpenCV HighGUI,
  * translating keycodes into abstract UserAction enumerations to drive the SLAM controller.
  */
class ControlPanel {
public:
    /**
     * @brief Polls the latest user input and returns the corresponding action.
     *
     * Intercepts keyboard events synchronously using non-blocking key polling (`cv::pollKey()`).
     *
     * @return UserAction The high-level user action requested (START, CALIBRATE, QUIT, or NONE if idle).
     */
    UserAction pollAction();
};