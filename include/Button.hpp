#pragma once
#include <string>

class Button {
private:
	std::string label;
	bool pressed;
public:
	Button(const std::string& label);
	bool isPressed() const;
};