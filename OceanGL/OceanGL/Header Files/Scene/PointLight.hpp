#pragma once

#include "Light.hpp"

class PointLight : public Light {
private:

	bool debug = false;

	glm::vec3 position;

	float attenuation_linear = 0.0;
	float attenuation_quadratic = 0.0;

	int id;

	inline static int instance_count = 0;

public:

	PointLight() : Light(glm::vec3(0), glm::vec3(0), glm::vec3(0)), position(glm::vec3(0)) { id = 0; }
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float linear, float quadratic);

	void update(const Shader& shader) const override;

	void draw_debug(bool b);

	const glm::vec3& get_position() const;
};