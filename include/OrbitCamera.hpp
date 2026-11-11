#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrbitCamera {
private:
	float yaw;
	float pitch;
	float distance;
	glm::vec3 target;

	float normalizeAngle(float angle);
public:
	OrbitCamera(float distance, float pitch);
	
	void rotate(float deltaYaw);
	void moveForward(float deltaYaw);
	void moveRight(float deltaYaw);
	const glm::mat4& getViewMatrix() const;


};