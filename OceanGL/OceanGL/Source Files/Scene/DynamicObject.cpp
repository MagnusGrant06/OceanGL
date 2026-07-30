#include "Scene/DynamicObject.hpp"

DynamicObject::DynamicObject(Mesh mesh, glm::mat4 model_matrix) : SceneObject(std::move(mesh), model_matrix) {}

const glm::mat4& DynamicObject::get_model_matrix() const { return model_matrix; }