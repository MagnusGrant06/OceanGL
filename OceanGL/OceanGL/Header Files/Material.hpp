#pragma once

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Scene/Scene.hpp"

class Material {
	glm::vec3 albedo;
	glm:: vec3 specular;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	float shininess;

public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) : albedo(albedo), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	void update(const Shader& shader) const;
};