#include "SlamMonocular.h"

int main(int argc, char** argv) {
	if (argc > 1 && std::string(argv[1]) == "--calibrate") {
		std::cout << "Lancement de la phase de calibration..." << std::endl;
		runCalibration();
		return 0; // On arrête le programme une fois calibré
	}

	return 0;
}
