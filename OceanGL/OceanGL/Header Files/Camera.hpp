#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Scene;

class Camera {
private:
	glm::vec3 cam_pos;
	glm::vec3 cam_front;
	glm::vec3 up_vec;

	bool first_mouse = true;
	double last_x = 400.0f;
	double last_y = 300.0f;

	float yaw = -90.0f;
	float pitch = 45.0f;


	glm::vec3 calculate_direction(float cam_yaw, float cam_pitch);

public:
	Camera();

	void update(float delta, Scene& scene);

	void process_mouse_input(double xpos, double ypos);

	const glm::mat4 get_view_matrix(glm::vec3 player_position) const;

	const glm::vec3 get_look_direction() const;

	const glm::vec3 get_cam_pos() const;


};