#pragma once

#include "StaticObject.hpp"

class TestMesh : public StaticObject {
public:
	TestMesh(std::shared_ptr<Mesh> mesh, glm::mat4 model) : StaticObject(std::move(mesh), model) {}

	void draw(glm::mat4 view, glm::mat4 proj) const override {
		mesh->get_shader().use();
		mesh->get_shader().set_mat4("view", view);
		mesh->get_shader().set_mat4("proj", proj);
		mesh->get_shader().set_mat4("model", model_matrix);
		mesh->draw_mesh();
	}

	const glm::mat4& get_model_matrix() const override {
		return model_matrix;
	}
};