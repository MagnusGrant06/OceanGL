#include "Material.hpp"

void Material::update(const Shader& shader) const {
	shader.use();
	shader.set_vec3("material.ambient", ambient);
	shader.set_vec3("material.diffuse", diffuse);
	shader.set_vec3("material.specular", specular);
	shader.set_float("material.shininess", shininess);
}