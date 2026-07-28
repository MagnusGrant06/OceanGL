#include "Camera.hpp"

glm::mat4 Camera::get_view_matrix() {
	return glm::lookAt(
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}