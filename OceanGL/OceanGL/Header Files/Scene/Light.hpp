#include <glm/glm.hpp>
#include "../Shader.hpp"

class Light {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec3 position;

public:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position) : ambient(ambient), diffuse(diffuse), specular(specular), position(position) {}
	Light() = default;

	void update(const Shader& shader) const;

	const glm::vec3 get_position() const;

	const glm::vec3 get_ambient() const;

	const glm::vec3 get_diffuse() const;

	const glm::vec3 get_specular() const;
};