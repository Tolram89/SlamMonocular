#include "../include/OrbitCamera.hpp"
#include <cmath>

float OrbitCamera::normalizeAngle(float angle)
{
    angle = std::fmod(angle, 360.0f);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

OrbitCamera::OrbitCamera(float distance, float pitch)
	:distance(distance), pitch(pitch), yaw(0.0f), target(glm::vec3(0,0,0))
{}

void OrbitCamera::rotate(float deltaYaw)
{
    yaw += deltaYaw;
    normalizeAngle(yaw);
}

void OrbitCamera::moveForward(float deltaYaw)
{}

void OrbitCamera::moveRight(float deltaYaw)
{}

const glm::mat4& OrbitCamera::getViewMatrix() const
{}
