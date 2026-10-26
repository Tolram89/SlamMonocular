#include "../include/UserInterface.hpp"

UserInterface::UserInterface()
	:videoWindow(VideoWindow("videoWindow")), mapWindow(MapWindow("mapWindow"))
{ 
	//todo
}

void UserInterface::showFrame(const FrameData& frame) const
{
	//todo
}

void UserInterface::showMap(const std::vector<cv::Point3f> map3D) const
{
	//todo
}

const UserAction& UserInterface::pollAction()
{
	// TODO: insérer une instruction return ici
	return UserAction::NONE;
}

void UserInterface::close()
{
	//todo
}
