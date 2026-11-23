/**
 * @file FreeCamera.hpp
 * @brief Declaration of the FreeCamera class for 3D SLAM map visualization.
 */

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

 /**
  * @class FreeCamera
  * @brief Fixed-altitude first-person camera for exploring a 3D SLAM map.
  *
  * Operates in the OpenCV world coordinate system (+X right, +Y down, +Z forward),
  * using (0, -1, 0) as the world up vector. The camera maintains a constant height
  * above the XZ ground plane and a fixed downward pitch angle to prevent gimbal lock.
  */
class FreeCamera {
private:
	float yaw;          ///< Horizontal azimuth angle around the Y axis (in degrees, [0, 360)).
	float pitch;        ///< Fixed downward elevation angle toward the ground plane (in degrees).
	float height;       ///< Constant altitude above the XZ plane (must be strictly positive).
	glm::vec3 position; ///< Camera eye position in world coordinates (x, -height, z).

	/**
	 * @brief Wraps an angle into the [0, 360) degree range.
	 * @param angle Input angle in degrees.
	 * @return Normalized angle in [0, 360) degrees.
	 */
	float normalizeAngle(float angle);

	/**
	 * @brief Computes the unit horizontal forward direction vector on the XZ plane.
	 * @return Unit direction vector (-sin(yaw), 0, cos(yaw)).
	 */
	glm::vec3 getHorizontalForward() const;

public:
	/**
	 * @brief Constructs a FreeCamera at a given altitude and downward pitch.
	 *
	 * Initializes yaw to 0 degrees and places the camera at (0, -height, 0).
	 *
	 * @param height Altitude above the XZ ground plane (must be > 0).
	 * @param pitch Fixed downward viewing angle in degrees.
	 * @throws std::invalid_argument If height is negative or zero (height <= 0.0f).
	 */
	FreeCamera(float height, float pitch);

	/**
	 * @brief Rotates the camera horizontally in place around the vertical Y axis.
	 * @param deltaYaw Yaw increment in degrees (positive turns left, negative turns right).
	 */
	void rotate(float deltaYaw);

	/**
	 * @brief Translates the camera horizontally along its current forward direction.
	 * @param delta Signed displacement distance along the XZ plane.
	 */
	void moveForward(float delta);

	/**
	 * @brief Translates the camera horizontally along its local right axis.
	 * @param delta Signed lateral displacement distance along the XZ plane.
	 */
	void moveRight(float delta);

	/**
	 * @brief Computes the OpenGL view matrix transforming world coordinates to camera space.
	 * @return 4x4 homogeneous view matrix.
	 */
	glm::mat4 getViewMatrix() const;
};