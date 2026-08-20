#include <glm/glm.hpp>
#include "../Shader.hpp"

class Light {
	glm::vec3 color;
	glm::vec3 direction;
	glm::vec3 position;

public:
	Light(glm::vec3 color, glm::vec3 direction, glm::vec3 position) : color(color), direction(direction), position(position) {}
	Light() = default;

	void update(const Shader& shader) const;

	const glm::vec3 get_color() const;

	const glm::vec3 get_direction() const;

	const glm::vec3 get_position() const;
};