#include "Camera.hpp"
#include "Scene/Scene.hpp"

Camera::Camera() : cam_pos(glm::vec3(0.0f, 0.0f, 10.0f)), cam_front(glm::vec3(0.0f, 0.0f, -1.0f)), up_vec(glm::vec3(0.0f, 1.0f, 0.0f)) {}


void Camera::update(float delta, Scene& scene) {
	glm::vec3 position = scene.get_player_position() - cam_front * 2.0f + glm::vec3(0.0f, 0.8f, 1.0f);
	cam_pos = position;
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

	double xoffset = xpos - last_x;
	double yoffset = ypos - last_y;
	last_x = xpos;
	last_y = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += static_cast<float>(xoffset);
	pitch -= static_cast<float>(yoffset);

	//clamp pitch values if out of range
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cam_front = calculate_direction(yaw, pitch);
}


const glm::mat4 Camera::get_view_matrix(glm::vec3 player_position) const {
	return glm::lookAt(cam_pos, player_position + cam_front * 10.0f, up_vec);
}

const glm::vec3 Camera::get_look_direction() const { return cam_front; }

const glm::vec3 Camera::get_cam_pos() const { return cam_pos; }