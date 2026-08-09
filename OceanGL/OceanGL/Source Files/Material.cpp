#include "Material.hpp"

void Material::update(const Shader& shader, const Scene& scene) {
	shader.use();
	shader.set_vec3("lightColor", scene.get_light().get_color());
	shader.set_vec3("objectColor", albedo);
	shader.set_vec3("lightPos", scene.get_light().get_position());
	shader.set_vec3("viewPos", scene.get_camera().get_look_direction());
}