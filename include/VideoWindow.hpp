#pragma once

#include "FrameData.hpp"

class VideoWindow {
private:
	std::string title;
public:
	VideoWindow(const std::string& title);
	void show(const FrameData& frame) const;
	void close();
};