#pragma once
#include <opencv2/features2d.hpp>
#include "FrameData.hpp"

class Tracking {
private:
	cv::Ptr<cv::DescriptorMatcher> matcher;
public:
	Tracking();
	bool estimatePose(FrameData& previous_frame, FrameData& current_frame);

};