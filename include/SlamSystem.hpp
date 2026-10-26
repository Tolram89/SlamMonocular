#pragma once
#include "VideoStream.hpp"
#include "Preprocessing.hpp"
#include "InterestPoints.hpp"
#include "Calibration.hpp"
#include "UserInterface.hpp"
#include "Tracking.hpp"
#include "Mapping.hpp"

class SlamSystem {
private:
	VideoStream& videoStream;
	Camera& camera;
	Preprocessing& preprocessing;
	InterestPoints& interestPoints;
	Calibration& calibration;
	std::shared_ptr<FrameData> previousFrame;
	UserInterface& ui;
	Tracking& tracking;
	Mapping mapping;

public:
	SlamSystem();
	bool init();
	void run();
	void step();
};