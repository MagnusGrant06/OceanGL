#include "Scene/DynamicObject.hpp"

DynamicObject::DynamicObject(std::shared_ptr<Mesh> mesh, glm::mat4 model_matrix, Material mat) : SceneObject(std::move(mesh), model_matrix, mat) {}

const glm::mat4& DynamicObject::get_model_matrix() const { return model_matrix; }