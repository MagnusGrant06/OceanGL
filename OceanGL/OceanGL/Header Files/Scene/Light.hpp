#pragma once

#include <glm/glm.hpp>
#include "../Shader.hpp"

class Light {

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

public:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular) {}

	virtual void update(const Shader& shader) const = 0;

	const glm::vec3& get_ambient() const { return ambient; }

	const glm::vec3& get_diffuse() const { return diffuse; }

	const glm::vec3& get_specular() const { return specular; }
};