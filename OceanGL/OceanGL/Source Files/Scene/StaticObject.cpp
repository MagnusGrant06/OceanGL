#include "Scene/StaticObject.hpp"

StaticObject::StaticObject(Mesh mesh, const glm::mat4 model) : SceneObject(std::move(mesh), model) {}

const glm::mat4& StaticObject::get_model_matrix() const { return model_matrix; }
