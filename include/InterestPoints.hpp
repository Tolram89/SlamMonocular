#pragma once
#include <opencv2/features2d.hpp>
#include "FrameData.hpp"

class InterestPoints {
private:
	cv::Ptr<cv::ORB> orb;
public:
	InterestPoints(int nfeatures);
	bool extract(const FrameData& frame);

};