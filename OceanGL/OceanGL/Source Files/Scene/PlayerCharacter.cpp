#include "Scene/PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(std::shared_ptr<Mesh> mesh, glm::mat4 model) : DynamicObject(std::move(mesh), model) {}

void PlayerCharacter::draw(glm::mat4 view, glm::mat4 proj) const{
	mesh->get_shader().use();
	mesh->get_shader().set_mat4("view", view);
	mesh->get_shader().set_mat4("proj", proj);
	mesh->draw_mesh();
}

void PlayerCharacter::update(float delta, Scene& scene) {

	mesh->get_shader().use();

	glm::vec3 cam_dir = scene.get_camera().get_look_direction();
	process_input(&scene.get_window(), delta, cam_dir);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 orientation = glm::inverse(glm::lookAt(glm::vec3(0.0f), cam_dir, up));

	glm::mat4 correction = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0,1,0));
	correction = glm::rotate(correction, glm::radians(90.0f), glm::vec3(1, 0, 0));

	model_matrix = glm::translate(glm::mat4(1.0f), global_position) * orientation * correction;

	mesh->get_shader().set_mat4("model", model_matrix);
}

void PlayerCharacter::process_input(GLFWwindow* window, float delta, glm::vec3 look_direction) {
	const float movement_speed = 2.5f * delta;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		global_position += movement_speed * look_direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		global_position -= movement_speed * look_direction;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		global_position -= glm::normalize(glm::cross(look_direction, up_vec)) * movement_speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		global_position += glm::normalize(glm::cross(look_direction, up_vec)) * movement_speed;
}

glm::mat4 PlayerCharacter::follow_camera(const Camera& cam) {
	return cam.get_view_matrix(global_position);
}

const glm::vec3 PlayerCharacter::get_position() const { return global_position; }