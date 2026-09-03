#include "Scene/Light.hpp"

void Light::update(const Shader& shader) const {
	shader.use();
	shader.set_vec3("light.position", position);
	shader.set_vec3("light.ambient", ambient);
	shader.set_vec3("light.diffuse", diffuse);
	shader.set_vec3("light.specular", specular);
}


const glm::vec3 Light::get_position() const { return position; }

const glm::vec3 Light::get_ambient() const { return ambient; }

const glm::vec3 Light::get_diffuse() const { return diffuse; }

const glm::vec3 Light::get_specular() const { return specular; }