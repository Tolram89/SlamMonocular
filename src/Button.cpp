#include "../include/Button.hpp"

Button::Button(const std::string& label)
	:label(label), pressed(false)
{}

bool Button::isPressed() const
{
	return pressed;
}

void Button::setPressed(bool pressed)
{
	this->pressed = pressed;
}
