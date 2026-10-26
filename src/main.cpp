#include <iostream>
#include "../include/Camera.hpp"

int main() {
    try
    {
        Camera camera1;
        std::cout << camera1.isCalibrated() << std::endl;
        cv::Mat K = (cv::Mat_<double>(3, 3) <<
            500, 0, 320,
            0, 500, 240,
            0, 0, 1);
        cv::Mat dist = cv::Mat::eye(cv::Size(5, 1), CV_64F);
        camera1.setIntrinsics(K, dist);
        std::cout << camera1.isCalibrated() << std::endl;
        camera1.saveIntrinsics("../config/calibration.yaml");
        Camera camera2;
        camera2.loadIntrinsics("../config/calibration.yaml");
        //std::cout << camera2.getCameramatrix() << std::endl;


    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur capturée : " << e.what() << std::endl;
    }
    


    return 0;
}
