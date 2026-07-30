#include "Camera.hpp"

Camera::Camera() : cam_pos(glm::vec3(0.0f, 0.0f, 10.0f)), cam_front(glm::vec3(0.0f, 0.0f, -1.0f)), up_vec(glm::vec3(0.0f, 1.0f, 0.0f)) {}

void Camera::process_input(GLFWwindow* window, float delta) {
	const float camera_speed = 2.5f * delta;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam_pos += camera_speed * cam_front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam_pos -= camera_speed * cam_front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam_pos -= glm::normalize(glm::cross(cam_front, up_vec)) * camera_speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam_pos += glm::normalize(glm::cross(cam_front, up_vec)) * camera_speed;
}

glm::vec3 Camera::calculate_direction(float cam_yaw, float cam_pitch) {
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));

	return glm::normalize(direction);
}

void Camera::process_mouse_input(double xpos, double ypos) {

	if (first_mouse) {
		xpos = last_x;
		ypos = last_y;
		first_mouse = false;
	}

	float xoffset = xpos - last_x;
	float yoffset = ypos - last_y;
	last_x = xpos;
	last_y = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch -= yoffset;

	//clamp pitch values if out of range
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cam_front = calculate_direction(yaw, pitch);
}

const glm::mat4 Camera::get_view_matrix() const {
	return glm::lookAt(cam_pos, cam_pos + cam_front, up_vec);
}