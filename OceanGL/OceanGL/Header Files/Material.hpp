#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Scene/Scene.hpp"

class Material {
	glm::vec3 albedo;
	float specular;
	float shininess;

public:
	Material(glm::vec3 albedo, float specular, float shininess) : albedo(albedo), specular(specular), shininess(shininess) {}

	void update(const Shader& shader) const;
};