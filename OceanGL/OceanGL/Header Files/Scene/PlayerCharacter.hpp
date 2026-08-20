#pragma once

#include "DynamicObject.hpp"
#include "Scene.hpp"

class PlayerCharacter : public DynamicObject {
private:
	glm::vec3 global_position = glm::vec3(0.0f);
	glm::vec3 up_vec = glm::vec3(0.0f, 1.0f, 0.0f);
public:

	PlayerCharacter(std::shared_ptr<Mesh> mesh, glm::mat4 model_matrix, Material mat);

	void draw(glm::mat4 view, glm::mat4 proj, glm::vec3 cam_pos) const override;

	void update(float delta, Scene& scene) override;

	void process_input(GLFWwindow* window, float delta, glm::vec3 look_direction);

	glm::mat4 follow_camera(const Camera& cam);

	const glm::vec3 get_position() const;

	const Mesh& get_mesh() const override;
};