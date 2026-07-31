#pragma once

#include <GLFW/glfw3.h>

#include "../Camera.hpp"

#include <vector>
#include <memory>
class SceneObject;
class DynamicObject;

class Scene {
private:
	std::vector<std::unique_ptr<SceneObject>> objects;

	Camera cam;
	glm::mat4 proj;
	GLFWwindow& window;
public:

	Scene(glm::mat4 proj, GLFWwindow& window);

	void draw() const ;

	void update(float delta);

	void add_object(std::unique_ptr<SceneObject> obj);

	const Camera get_camera() const;

	GLFWwindow& get_window() const;
};