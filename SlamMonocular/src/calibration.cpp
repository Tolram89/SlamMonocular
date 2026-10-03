#include "calibration.h"
#include <iostream>

void runCalibration() {
    cv::VideoCapture cap(0, cv::CAP_DSHOW);
    //Dshow est l'ancienne api de windows, on la précise car sinon ça prend trop de temps à rechercher automatiquement
    //et on choisit dshow et pas msfi (l'api moderne) car cette derniere est trop lente à démarrer on gagne pratiquement 5s

    if (!cap.isOpened()) {
        std::cerr << "La webcam ne s'est pas ouverte" << std::endl;
        return;
    }

    cv::Mat frame;
    std::vector<cv::Point2f> corners;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    int64 t_actuel = 0;
    int64 t_precedent = 0;

    while (true) {
        cap.read(frame);
        if (frame.empty()) break;

        t_actuel = cv::getTickCount();
        bool patternWasFound = cv::findChessboardCorners(frame, cv::Size(9, 6), corners, cv::CALIB_CB_ADAPTIVE_THRESH);
        cv::drawChessboardCorners(frame, cv::Size(9, 6), corners, patternWasFound);

        if (patternWasFound && (t_actuel - t_precedent) / cv::getTickFrequency() > 2) {
            imagePoints.push_back(corners);
            t_precedent = t_actuel;
            std::cout << "Capture : " << imagePoints.size() << "/20" << std::endl;
        }

        cv::imshow("Calibration", frame);

        if (cv::waitKey(30) > 0) break;
        if (imagePoints.size() >= 20) break;
    }

    cv::destroyWindow("Calibration"); 

    float squareSize = 0.8f; //  represente la taille du carreau, ici 0.8 cm sur mon tel
    std::vector<std::vector<cv::Point3f>> objectPoints(1);

    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 9; ++x) {
            objectPoints.at(0).push_back(cv::Point3f{ x * squareSize, y * squareSize, 0 });
        }
    }
    objectPoints.resize(imagePoints.size(), objectPoints.at(0));

    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;

    std::cout << "Calcul en cours..." << std::endl;
    cv::calibrateCamera(objectPoints, imagePoints, frame.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
    std::cout << "Matrice de la camera : \n" << cameraMatrix << std::endl;

    cv::FileStorage fs("calibration.yaml", cv::FileStorage::WRITE);
    fs << "cameraMatrix" << cameraMatrix;
    fs << "distCoeffs" << distCoeffs;
    fs.release();
    std::cout << "Fichier calibration.yaml sauvegarde avec succes." << std::endl;
}