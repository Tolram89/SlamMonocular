#include "preprocessing.h"
#include <stdexcept> 

CameraConfig readParameter()
{
	cv::FileStorage fs("calibration.yaml", cv::FileStorage::READ);
	if( !fs.isOpened())
		throw std::runtime_error("Impossible d'ouvrir le fichier : calibration.yaml");
	cv::Mat cameraMatrix, distCoeffs;
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;
	
	return CameraConfig{ cameraMatrix, distCoeffs };
}
