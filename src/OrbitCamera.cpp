#include "../include/OrbitCamera.hpp"
#include <cmath>
#include <stdexcept>

float OrbitCamera::normalizeAngle(float angle)
{
    angle = std::fmod(angle, 360.0f);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

glm::vec3 OrbitCamera::getHorizontalForward() const
{
    float yaw_rad = glm::radians(yaw);
    return glm::vec3(-glm::sin(yaw_rad), 0, glm::cos(yaw_rad));
}

OrbitCamera::OrbitCamera(float distance, float pitch)
	:distance(distance), pitch(pitch), yaw(0.0f), target(glm::vec3(0,0,0))
{
    if (distance <= 0.0) {
        throw std::invalid_argument("Distance cannot be negative or null");
    }
}

void OrbitCamera::rotate(float deltaYaw)
{
    yaw += deltaYaw;
    yaw = normalizeAngle(yaw);
}

void OrbitCamera::moveForward(float delta)
{
    glm::vec3 fxz = getHorizontalForward();
    target += delta * fxz;
}

void OrbitCamera::moveRight(float delta)
{
    glm::vec3 fxz = getHorizontalForward();
    glm::vec3 u_monde(0, -1, 0);
    glm::vec3 rxy = glm::normalize(glm::cross(fxz, u_monde));
    target += delta * rxy;

}

glm::mat4 OrbitCamera::getViewMatrix() const
{
    float yaw_rad = glm::radians(yaw);
    float pitch_rad = glm::radians(pitch);

    glm::vec3 offset;
    offset.x = distance * std::cos(pitch_rad) * std::sin(yaw_rad);
    offset.y = -distance * std::sin(pitch_rad); 
    offset.z = -distance * std::cos(pitch_rad) * std::cos(yaw_rad);
    return glm::lookAt(target + offset, target, glm::vec3(0,-1,0));
}
