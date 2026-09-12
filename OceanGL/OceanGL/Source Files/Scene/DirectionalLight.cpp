#include "Scene/DirectionalLight.hpp"

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) : Light(ambient, diffuse, specular), direction(direction) {}

void DirectionalLight::update(const Shader& shader) const {
	shader.use();
	shader.set_vec3("dirLight.direction", direction);
	shader.set_vec3("dirLight.ambient", ambient);
	shader.set_vec3("dirLight.diffuse", diffuse);
	shader.set_vec3("dirLight.specular", specular);
}

const glm::vec3& DirectionalLight::get_direction() const { return direction; }