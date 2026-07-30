#pragma once

#include "../Camera.hpp"

#include <vector>
#include <memory>
class SceneObject;
class DynamicObject;

class Scene {
private:
	std::vector<std::unique_ptr<SceneObject>> objects;

	Camera& cam;
	glm::mat4 proj;
public:

	Scene(glm::mat4 proj, Camera& cam);

	void draw() const ;

	void update(float delta);

	void add_object(std::unique_ptr<SceneObject> obj);
};