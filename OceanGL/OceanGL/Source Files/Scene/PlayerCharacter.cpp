#include "Scene/PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(Mesh mesh, glm::mat4 model) : DynamicObject(std::move(mesh), model) {
	model_matrix = glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model_matrix = glm::rotate(model_matrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
}

void PlayerCharacter::draw(glm::mat4 view, glm::mat4 proj) const{
	mesh.get_shader().use();
	mesh.get_shader().set_mat4("view", view);
	mesh.get_shader().set_mat4("proj", proj);
	mesh.draw_mesh();
}

void PlayerCharacter::update(float delta, Scene& scene) {
	mesh.get_shader().use();
	model_matrix = glm::rotate(model_matrix, delta * glm::radians(50.0f), glm::vec3(0, 0, 1));
	mesh.get_shader().set_mat4("model", model_matrix);
}

glm::mat4 PlayerCharacter::follow_camera(const Camera& cam) {
	return cam.get_view_matrix();
}