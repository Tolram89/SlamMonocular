#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
int simulated_key= -1;
namespace cv{
	int getSimulatedKey()
	{
		return simulated_key;
	}
}

#define pollKey getSimulatedKey

#include "../src/ControlPanel.cpp"

TEST(ControlPanel, TestDefaultBehavior)
{
	simulated_key = -1;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::NONE);
}
TEST(ControlPanel, TestDefaultBehaviorWithRandomKey)
{
	simulated_key = 32;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::NONE);
}
TEST(ControlPanel, TestStartWithSKey)
{
	simulated_key = 83;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::START);
}
TEST(ControlPanel, TestStartWithsKey)
{
	simulated_key = 115;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::START);
}
TEST(ControlPanel, TestCalibrateWithCKey)
{
	simulated_key = 67;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::CALIBRATE);
}
TEST(ControlPanel, TestCalibrateWithcKey)
{
	simulated_key = 99;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::CALIBRATE);
}
TEST(ControlPanel, TestQuitWithQKey)
{
	simulated_key = 81;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::QUIT);
}
TEST(ControlPanel, TestQuitWithqKey)
{
	simulated_key = 113;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::QUIT);
}
TEST(ControlPanel, TestQuitWithEscKey)
{
	simulated_key = 27;
	ControlPanel c;
	EXPECT_TRUE(c.pollAction() == UserAction::QUIT);
}