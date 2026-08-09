#include "Scene/Light.hpp"

const glm::vec3 Light::get_color() const { return color; }

const glm::vec3 Light::get_direction() const { return direction; }

const glm::vec3 Light::get_position() const { return position; }