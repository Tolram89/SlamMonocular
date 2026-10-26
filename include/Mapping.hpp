#pragma once
#include "FrameData.hpp"

class Mapping {
private:
	std::vector<cv::Point3f> map3D;
public:
	Mapping();

	bool update(FrameData& previous_frame, FrameData& current_frame);
	const std::vector<cv::Point3f>& getMap() const;

};