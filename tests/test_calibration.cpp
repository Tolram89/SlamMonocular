#include <gtest/gtest.h>
#include "../include/Calibration.hpp"
#include <opencv2/opencv.hpp>
#include <vector>



TEST(Calibration, TestConstructorWithIncorrectSquareSize)
{
    EXPECT_THROW(Calibration(-1, cv::Size(9, 7)), std::invalid_argument);
}

TEST(Calibration, TestConstructorWithIncorrectPatternSize)
{
    EXPECT_THROW(Calibration(2, cv::Size(-1, 7)), std::invalid_argument);
}
TEST(Calibration, TestConstructorWithCorrectParameter)
{
    EXPECT_NO_THROW(Calibration(2, cv::Size(9, 7)));
   
}

TEST(Calibration, TestAddFrameWithCorrectFrame)
{
    Calibration calibration(2, cv::Size(9, 6));
    auto camera = std::make_shared<Camera>();
    cv::Mat image = cv::imread(std::string(TEST_DATA_DIR) + "pattern1.png", cv::IMREAD_COLOR);
    FrameData frame(1, image, camera);
    EXPECT_TRUE(calibration.addFrame(frame));
    EXPECT_TRUE(calibration.getFrameCount() == 1);

}
TEST(Calibration, TestAddFrameWithIncorrectFrame)
{
    Calibration calibration(2, cv::Size(9, 6));
    auto camera = std::make_shared<Camera>();
    cv::Mat image = cv::imread(std::string(TEST_DATA_DIR) + "incorrectFrame.png", cv::IMREAD_COLOR);
    FrameData frame(1, image, camera);
    EXPECT_FALSE(calibration.addFrame(frame));
    EXPECT_TRUE(calibration.getFrameCount() == 0);

}

TEST(Calibration, TestCalibrateWithNotEnoughFrame)
{
    Calibration calibration(2, cv::Size(9, 6));
    auto camera = std::make_shared<Camera>();
    cv::Mat image = cv::imread(std::string(TEST_DATA_DIR) + "pattern1.png", cv::IMREAD_COLOR);
    FrameData frame(1, image, camera);
    EXPECT_TRUE(calibration.addFrame(frame));
    EXPECT_FALSE(calibration.calibrate(*camera));

}
TEST(Calibration, TestCalibrateWithEnoughFrame)
{
    Calibration calibration(2, cv::Size(9, 6));
    auto camera = std::make_shared<Camera>();
    cv::Mat baseImage = cv::imread(std::string(TEST_DATA_DIR) + "pattern1.png", cv::IMREAD_COLOR);

    for (int i = 0; i < 20; ++i)
    {
        cv::Mat image;
        // Rotation progressive entre -10° et +10° pour conserver tous les coins dans l'image
        double angle = -10.0 + i * (20.0 / 20.0);
        cv::Point2f centre((baseImage.cols - 1) / 2.0, (baseImage.rows - 1) / 2.0);
        cv::Mat matriceRotation = cv::getRotationMatrix2D(centre, angle, 1.0);
        cv::warpAffine(baseImage, image, matriceRotation, baseImage.size());

        FrameData frame(i, image, camera);
        EXPECT_TRUE(calibration.addFrame(frame));
    }

    EXPECT_TRUE(calibration.calibrate(*camera));
    EXPECT_TRUE(camera->isCalibrated());

}

