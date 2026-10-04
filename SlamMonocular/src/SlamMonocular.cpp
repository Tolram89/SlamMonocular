#include "SlamMonocular.h"

int main(int argc, char** argv) {
	if (argc > 1 && std::string(argv[1]) == "--calibrate") {
		std::cout << "Lancement de la phase de calibration..." << std::endl;
		runCalibration();
		return 0; // On arrête le programme une fois calibré
	}
	try {
		CameraConfig camera_config = readParameter();
		std::cout << camera_config.cameraMatrix << camera_config.distCoeffs << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	

	return 0;
}
