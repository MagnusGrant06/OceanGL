#include "Scene/Scene.hpp"
#include "Scene/SceneObject.hpp"
#include "Scene/DynamicObject.hpp"

Scene::Scene(glm::mat4 proj, Camera& cam, GLFWwindow& window) : proj(proj), cam(cam), window(window) {}

void Scene::draw() const {
	for (auto& obj : objects) {
		obj->draw(cam.get_view_matrix(), proj);
	}
}

void Scene::update(float delta) {
	for (auto& obj : objects) {
		if (auto* dynamic = dynamic_cast<DynamicObject*>(obj.get())) {
			dynamic->update(delta, *this);
		}
	}
}

void Scene::add_object(std::unique_ptr<SceneObject> obj) {
	objects.push_back(std::move(obj));
}

const Camera& Scene::get_camera() const { return cam; }

GLFWwindow& Scene::get_window() const { return window; }