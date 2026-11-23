#include <gtest/gtest.h>
#include "../include/FreeCamera.hpp"

TEST(FreeCamera, TestConstructor)
{
	EXPECT_NO_THROW(FreeCamera free(10, 45));

	EXPECT_THROW(FreeCamera notfree(-5, 45), std::invalid_argument);

}

TEST(FreeCamera, TestInitialProjection)
{
	FreeCamera free(10, 30);
	glm::vec4 camera_point(0, -10.0f, 0.0f, 1.0f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).x, glm::vec4(0, 0, 0, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).y, glm::vec4(0, 0, 0, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).z, glm::vec4(0, 0, 0, 1).z, 10e-4f);
}

TEST(FreeCamera, TestFrontProjection)
{
	FreeCamera free(10, 45);
	glm::vec4 front_point(0, -10.0f + glm::sin(glm::pi<double>() / 4), glm::cos(glm::pi<double>() / 4), 1.0f);
	EXPECT_NEAR((free.getViewMatrix() * front_point).x, glm::vec4(0, 0, -1, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * front_point).y, glm::vec4(0, 0, -1, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * front_point).z, glm::vec4(0, 0, -1, 1).z, 10e-4f);
}

TEST(FreeCamera, TestMoveForwardProjection)
{
	FreeCamera free(10, 45);
	free.moveForward(5);
	glm::vec4 forward_point(0.0f, -10.0f, 5.0f, 1.0f);
	EXPECT_NEAR((free.getViewMatrix() * forward_point).x, glm::vec4(0, 0, 0, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * forward_point).y, glm::vec4(0, 0, 0, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * forward_point).z, glm::vec4(0, 0, 0, 1).z, 10e-4f);
}

TEST(FreeCamera, TestMoveRightProjection)
{
	FreeCamera free(10, 45);
	free.moveRight(5);
	glm::vec4 right_point(5.0f, -10.0f, 0.0f, 1.0f);
	EXPECT_NEAR((free.getViewMatrix() * right_point).x, glm::vec4(0, 0, 0, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * right_point).y, glm::vec4(0, 0, 0, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * right_point).z, glm::vec4(0, 0, 0, 1).z, 10e-4f);
}

TEST(FreeCamera, Test360RotationProjection)
{
	FreeCamera free(10, 45);
	glm::vec4 camera_point(0, -10.0f, 0.0f, 1.0f);
	free.rotate(360);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).x, glm::vec4(0, 0, 0, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).y, glm::vec4(0, 0, 0, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).z, glm::vec4(0, 0, 0, 1).z, 10e-4f);
}

TEST(FreeCamera, TestRotationAndMoveProjection)
{
	FreeCamera free(10, 45);
	glm::vec4 camera_point(-5, -10.0f, 0.0f, 1.0f);
	free.rotate(90);
	free.moveForward(5);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).x, glm::vec4(0, 0, 0, 1).x, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).y, glm::vec4(0, 0, 0, 1).y, 10e-4f);
	EXPECT_NEAR((free.getViewMatrix() * camera_point).z, glm::vec4(0, 0, 0, 1).z, 10e-4f);
}