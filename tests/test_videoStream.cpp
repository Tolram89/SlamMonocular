#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "VideoStream.hpp"

class VideoStreamFixture : public ::testing::Test {
protected:
	void SetUp() override {
		auto test_name = std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".avi";
		path = (std::filesystem::temp_directory_path() / test_name).string();

		cv::VideoWriter writer(
			path,
			cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
			1.0,
			cv::Size(100, 100)
		);

		if (!writer.isOpened()) {
			std::cerr << "Erreur d'ouverture du VideoWriter avec MJPEG" << std::endl;
			throw std::runtime_error("Couldn't open the file");
		}

		cv::Mat black_frame = cv::Mat::zeros(100, 100, CV_8UC3);

		for (int i = 0; i < number_frames; ++i) {
			writer.write(black_frame);
		}

		writer.release();
	}

	void TearDown() override {
		if (std::filesystem::exists(path)) {
			std::filesystem::remove(path);
		}
	}

	std::string path;
	int number_frames = 4;
};


TEST(VideoStream, TestOpenIncorrectFile)
{

	EXPECT_THROW(VideoStream videoStream("IncorrectFile/incorrect_file.mp4"), std::runtime_error);

}

TEST_F(VideoStreamFixture, TestOpenCorrectFileAndReadOk)
{
	VideoStream videoStream(path);
	EXPECT_TRUE(videoStream.isOpened());
	cv::Mat frame;
	EXPECT_TRUE(videoStream.read(frame));
	EXPECT_FALSE(frame.empty());
	for (int i = 0; i < number_frames - 1; ++i)
	{
		videoStream.read(frame);
	}
	EXPECT_FALSE(videoStream.read(frame));
}