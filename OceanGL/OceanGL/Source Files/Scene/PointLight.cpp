#include "Scene/PointLight.hpp"

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float linear, float quadratic) :
	Light(ambient, diffuse, specular), position(position),
	attenuation_linear(linear), attenuation_quadratic(quadratic) {

	id = instance_count;
	instance_count++;
}

void PointLight::update(const const Shader& shader) const{
	shader.use();
	shader.set_int("lightNum", instance_count);
	shader.set_float("pointLights[" + std::to_string(id) + "].constant", 1.0);
	shader.set_float("pointLights[" + std::to_string(id) + "].linear", attenuation_linear);
	shader.set_float("pointLights[" + std::to_string(id) + "].quadratic", attenuation_quadratic);
	shader.set_vec3("pointLights[" + std::to_string(id) + "].position", position);
	shader.set_vec3("pointLights[" + std::to_string(id) + "].ambient", ambient);
	shader.set_vec3("pointLights[" + std::to_string(id) + "].diffuse", diffuse);
	shader.set_vec3("pointLights[" + std::to_string(id) + "].specular", specular);
}

bool PointLight::draw_debug(bool b) { debug = b; }

const glm::vec3& PointLight::get_position() const { return position; }