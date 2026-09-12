#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Camera.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

#include <vector>
#include <memory>

class SceneObject;
class DynamicObject;
class PlayerCharacter;

class Scene {
private:
	std::unique_ptr<PlayerCharacter> player;
	std::vector<std::unique_ptr<SceneObject>> objects;
	std::vector<std::unique_ptr<Light>> lights;

	Camera cam;
	glm::mat4 proj;
	GLFWwindow& window;

	PointLight light;
	DirectionalLight dirLight;

public:

	Scene(glm::mat4 proj, GLFWwindow& window, std::unique_ptr<PlayerCharacter> player);

	void setup_scene();

	void draw() const ;

	void update(float delta);

	void add_object(std::unique_ptr<SceneObject> obj);

	const Camera get_camera() const;

	GLFWwindow& get_window() const;

	const glm::vec3 get_player_position() const;

	const Light& get_light() const;
};