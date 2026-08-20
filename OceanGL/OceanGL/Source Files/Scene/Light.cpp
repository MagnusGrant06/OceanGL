#include "Scene/Light.hpp"

void Light::update(const Shader& shader) const {
	shader.use();
	shader.set_vec3("lightPos", position);
	shader.set_vec3("lightColor", color);
}

const glm::vec3 Light::get_color() const { return color; }

const glm::vec3 Light::get_direction() const { return direction; }

const glm::vec3 Light::get_position() const { return position; }
