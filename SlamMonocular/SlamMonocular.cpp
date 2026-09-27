// SlamMonocular.cpp : définit le point d'entrée de l'application.
//

#include "SlamMonocular.h"


int main()
{
	cv::VideoCapture cap(0, cv::CAP_DSHOW);
	//Dshow est l'ancienne api de windows, on la précise car sinon ça prend trop de temps à rechercher automatiquement
	//et on choisit dshow et pas msfi (l'api moderne) car cette derniere est trop lente à démarrer on gagne pratiquement 5s

	if (!cap.isOpened())
	{
		std::cerr << "La webcam ne s'est pas ouverte" << std::endl;
		return -1;
	}

	cv::Mat frame;
	while (true) {
		cap.read(frame);
		if (frame.empty())
			break;
		cv::imshow("SlamMonocular", frame);

		if (cv::waitKey(30) > 0)
			break;
	
	}

	return 0;
}
