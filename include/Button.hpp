#pragma once
#include <string>

/**
 * @class Button
 * @brief Represents an abstract UI button for triggering user actions.
 *
 * Holds the interaction state (pressed/released) and a text label.
 * The state is typically updated by a container like ControlPanel.
 */
class Button {
private:
    std::string label; ///< Human-readable label of the button.
    bool pressed;      ///< Interaction state of the button.

public:
    /**
     * @brief Constructs a Button with a specified label.
     * @param label Text identifier for the button.
     */
    explicit Button(const std::string& label);

    /**
     * @brief Checks if the button is currently in a pressed state.
     * @return true if the button is pressed, false otherwise.
     */
    [[nodiscard]] bool isPressed() const;

    /**
     * @brief Sets the pressed state of the button.
     * @param pressed New state to assign (true for pressed, false for released).
     */
    void setPressed(bool pressed);
};