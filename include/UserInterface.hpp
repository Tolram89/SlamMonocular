#pragma once
#include "ControlPanel.hpp"
#include "MapWindow.hpp"
#include "VideoWindow.hpp"

class UserInterface {
private:
	ControlPanel controlPanel;
	MapWindow mapWindow;
	VideoWindow videoWindow;
public:
	UserInterface();

	void showFrame(const FrameData& frame) const;
	void showMap(const std::vector<cv::Point3f> map3D) const;
	const UserAction& pollAction();
	void close();

};