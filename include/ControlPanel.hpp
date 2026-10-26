#pragma once
#include <vector>
#include "Button.hpp"
#include "UserAction.hpp"

class ControlPanel {
private:
	std::vector<Button> buttons;
public:
	ControlPanel();
	const UserAction& pollAction();
};