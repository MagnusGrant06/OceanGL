#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Mesh.hpp"

//highest level class for any object within the scene, all to be drawn dynamically
class SceneObject {
protected:
	std::shared_ptr<Mesh> mesh;
	glm::mat4 model_matrix;

	SceneObject(std::shared_ptr<Mesh> mesh, glm::mat4 model_matrix) : mesh(std::move(mesh)), model_matrix(model_matrix) {};

public:
	virtual ~SceneObject() = default;

	SceneObject(const SceneObject&) = delete;
	SceneObject& operator=(const SceneObject&) = delete;

	SceneObject(SceneObject&&) noexcept = default;
	SceneObject& operator=(SceneObject&&) noexcept = default;

	virtual void draw(glm::mat4 view, glm::mat4 proj) const = 0;
	virtual const glm::mat4& get_model_matrix() const = 0;
};