#pragma once
#include <string>
#include <vector>
#include <opencv2/core/mat.hpp>

class MapWindow {
private:
	std::string title;
public:
	MapWindow(const std::string& title);
	void render(const std::vector<cv::Point3f> map3D) const;
	void close();
};