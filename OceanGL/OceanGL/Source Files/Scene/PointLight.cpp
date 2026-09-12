#include "Scene/PointLight.hpp"

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float linear, float quadratic) : Light(ambient, diffuse, specular), position(position), attenuation_linear(linear), attenuation_quadratic(quadratic) {}

void PointLight::update(const const Shader& shader) const{
	shader.use();
	shader.set_float("pointLight.constant", 1.0);
	shader.set_float("pointLight.linear", attenuation_linear);
	shader.set_float("pointLight.quadratic", attenuation_quadratic);
	shader.set_vec3("pointLight.position", position);
	shader.set_vec3("pointLight.ambient", ambient);
	shader.set_vec3("pointLight.diffuse", diffuse);
	shader.set_vec3("pointLight.specular", specular);
}

const glm::vec3& PointLight::get_position() const { return position; }