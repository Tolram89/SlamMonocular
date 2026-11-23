#include "../include/FreeCamera.hpp"
#include <cmath>
#include <stdexcept>

float FreeCamera::normalizeAngle(float angle)
{
    angle = std::fmod(angle, 360.0f);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

glm::vec3 FreeCamera::getHorizontalForward() const
{
    float yaw_rad = glm::radians(yaw);
    return glm::vec3(-glm::sin(yaw_rad), 0, glm::cos(yaw_rad));
}

FreeCamera::FreeCamera(float height, float pitch)
	:height(height), pitch(pitch), yaw(0.0f), position(glm::vec3(0,-height,0))
{
    if (height <= 0.0) {
        throw std::invalid_argument("Height cannot be negative or null");
    }
}

void FreeCamera::rotate(float deltaYaw)
{
    yaw += deltaYaw;
    yaw = normalizeAngle(yaw);
}

void FreeCamera::moveForward(float delta)
{
    glm::vec3 fxz = getHorizontalForward();
    position += delta * fxz;
}

void FreeCamera::moveRight(float delta)
{
    glm::vec3 fxz = getHorizontalForward();
    glm::vec3 u_monde(0, -1, 0);
    glm::vec3 rxy = glm::normalize(glm::cross(fxz, u_monde));
    position += delta * rxy;

}

glm::mat4 FreeCamera::getViewMatrix() const
{
    float yaw_rad = glm::radians(yaw);
    float pitch_rad = glm::radians(pitch);

    glm::vec3 d_regard(-glm::cos(pitch_rad) * glm::sin(yaw_rad), glm::sin(pitch_rad), glm::cos(pitch_rad) * glm::cos(yaw_rad));

    return glm::lookAt(position, position + d_regard, glm::vec3(0,-1,0));
}
