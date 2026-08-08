#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Camera.hpp"

#include <vector>
#include <memory>

class SceneObject;
class DynamicObject;
class PlayerCharacter;

class Scene {
private:
	std::unique_ptr<PlayerCharacter> player;
	std::vector<std::unique_ptr<SceneObject>> objects;

	Camera cam;
	glm::mat4 proj;
	GLFWwindow& window;

	glm::vec3 light_pos = glm::vec3(1.2f, 1.0f, 1.0f);

	glm::vec3 object_color = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 light_color = glm::vec3(1.0f);

public:

	Scene(glm::mat4 proj, GLFWwindow& window, std::unique_ptr<PlayerCharacter> player);

	void draw() const ;

	void update(float delta);

	void add_object(std::unique_ptr<SceneObject> obj);

	const Camera get_camera() const;

	GLFWwindow& get_window() const;

	const glm::vec3 get_player_position() const;
};