#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "Camera.hpp"

TEST(Camera, TestSetIntrinsicsWithCorrectMat) {
	Camera c;
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	bool ok = c.setIntrinsics(K, dist);
	EXPECT_TRUE(ok);	
}

TEST(Camera, TestSetIntrinsicsWithIncorrectMatKSize) {
	Camera c;
	cv::Mat K = (cv::Mat_<double>(2, 2) <<
		500, 0,
		320, 0
		);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	bool ok = c.setIntrinsics(K, dist);
	EXPECT_FALSE(ok);
	EXPECT_FALSE(c.isCalibrated());
}

TEST(Camera, TestSetIntrinsicsWithIncorrectMatDistSize) {
	Camera c;
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(2, 1), CV_64F);
	bool ok = c.setIntrinsics(K, dist);
	EXPECT_FALSE(ok);
	EXPECT_FALSE(c.isCalibrated());

}

TEST(Camera, TestSetIntrinsicsWithIncorrectMatKCoeff) {
	Camera c;
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		-1, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	bool ok = c.setIntrinsics(K, dist);
	EXPECT_FALSE(ok);
	EXPECT_FALSE(c.isCalibrated());

}

class CameraFixture : public ::testing::Test {
protected:
	void SetUp() override {
		path = (std::filesystem::temp_directory_path() / ::testing::UnitTest::GetInstance()->current_test_info()->name()).string();
		
	}
	void TearDown() override {
		std::filesystem::remove(path);
	}   

	std::string path = "";
	Camera camera1;
	Camera camera2;
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
};

TEST_F(CameraFixture, TestBackAndForth)
{
	EXPECT_TRUE(camera1.setIntrinsics(K, dist));

	std::cout << camera1.isCalibrated() << std::endl;
	EXPECT_TRUE(camera1.saveIntrinsics(path));
	
	EXPECT_TRUE(camera2.loadIntrinsics(path));
	EXPECT_EQ(cv::norm(camera1.getCameraMatrix(), camera2.getCameraMatrix(), cv::NORM_INF), 0.0);
	EXPECT_EQ(cv::norm(camera1.getDistCoeffs(), camera2.getDistCoeffs(), cv::NORM_INF), 0.0);
	
}

TEST(Camera, TestLoadIncorrectFile)
{
	Camera camera;
	EXPECT_FALSE(camera.loadIntrinsics("file_incorrect.yaml"));
	
}

TEST(Camera, TestSaveNotCalibratedCamera)
{
	Camera camera;
	EXPECT_FALSE(camera.saveIntrinsics("calibration_test.yaml"));
	EXPECT_FALSE(std::filesystem::exists("calibration_test.yaml"));
}

TEST_F(CameraFixture, TestLoadWithIncorrectDist)
{
	cv::FileStorage fs(path, cv::FileStorage::WRITE);
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist_incorrect = cv::Mat::zeros(cv::Size(4, 1), CV_64F);
	fs << "cameraMatrix" << K;
	fs << "distCoeffs" << dist_incorrect;
	fs.release();
	Camera camera;
	EXPECT_FALSE(camera.loadIntrinsics(path));
	std::filesystem::remove(path);

}
TEST(Camera, TestSetWithK32F)
{
	cv::Mat K = (cv::Mat_<float>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	Camera camera;
	EXPECT_TRUE(camera.setIntrinsics(K, dist));

	EXPECT_EQ(camera.getCameraMatrix().type(), CV_64F);
}

TEST(Camera, TestSetWithK8U)
{
	cv::Mat K = (cv::Mat_<uchar>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	Camera camera;
	EXPECT_FALSE(camera.setIntrinsics(K, dist));

}

TEST(Camera, TestSaveInIncorrectPath)
{
	std::string incorrect_path = "incorretDir/incorrectFile.yaml";
	Camera camera;
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	cv::Mat dist = cv::Mat::zeros(cv::Size(5, 1), CV_64F);
	EXPECT_TRUE(camera.setIntrinsics(K, dist));
	EXPECT_FALSE(camera.saveIntrinsics(incorrect_path));
}

TEST(Camera, TestIncorrectFile)
{
	std::string path = "test.yaml";
	cv::FileStorage fs(path, cv::FileStorage::WRITE);
	EXPECT_FALSE(!fs.isOpened());
	cv::Mat K = (cv::Mat_<double>(3, 3) <<
		500, 0, 320,
		0, 500, 240,
		0, 0, 1);
	fs << "cameraMatrix" << K;
	fs.release();
	Camera camera;
	EXPECT_FALSE(camera.loadIntrinsics(path));

	std::filesystem::remove(path);
	
}