#include "Scene/StaticObject.hpp"

StaticObject::StaticObject(std::shared_ptr<Mesh> mesh, const glm::mat4 model, Material mat) : SceneObject(std::move(mesh), model, mat) {}

const glm::mat4& StaticObject::get_model_matrix() const { return model_matrix; }
