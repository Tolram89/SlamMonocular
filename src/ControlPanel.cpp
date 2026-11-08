#include "../include/ControlPanel.hpp"
#include <opencv2/opencv.hpp>


UserAction ControlPanel::pollAction()
{
	int key = cv::pollKey();
	
	switch (key)
	{
		case -1 :
			return UserAction::NONE;
		case 83: //S
			[[fallthrough]];
		case 115: //s
			return UserAction::START;
		case 67: //C
			[[fallthrough]];
		case 99: //c
			return UserAction::CALIBRATE;
		case 27: //escape
			[[fallthrough]];
		case 81: //Q
			[[fallthrough]];
		case 113: //q
			return UserAction::QUIT;
		default:
			break;
	}

	return UserAction::NONE;

}
