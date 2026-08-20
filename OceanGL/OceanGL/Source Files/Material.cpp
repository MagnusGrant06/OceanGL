#include "Material.hpp"

void Material::update(const Shader& shader) const {
	shader.use();
	shader.set_vec3("objectColor", albedo);
}