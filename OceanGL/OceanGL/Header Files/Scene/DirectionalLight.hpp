#pragma once

#include "Light.hpp"
#include "../Shader.hpp"

class DirectionalLight : public Light {
	glm::vec3 direction;

public:
	DirectionalLight() : Light(glm::vec3(0), glm::vec3(0), glm::vec3(0)), direction(glm::vec3(0)) {}

	DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);

	void update(const Shader& shader) const override;

	const glm::vec3& get_direction() const;
};