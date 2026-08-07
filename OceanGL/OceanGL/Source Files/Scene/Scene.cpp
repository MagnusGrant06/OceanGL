#include "Scene/Scene.hpp"
#include "Scene/SceneObject.hpp"
#include "Scene/DynamicObject.hpp"
#include "Scene/PlayerCharacter.hpp"
#include "Scene/TestMesh.hpp"

Scene::Scene(glm::mat4 proj, GLFWwindow& window, std::unique_ptr<PlayerCharacter> player) : proj(proj), window(window), player(std::move(player)) {

	//accept mouse input
	glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(&window, &cam);

	//small captureless lambda to use as function pointer to mouse input calcs
	glfwSetCursorPosCallback(&window, [](GLFWwindow* lambda_window, double xpos, double ypos) {
		auto* self = static_cast<Camera*>(glfwGetWindowUserPointer(lambda_window));
		self->process_mouse_input(xpos, ypos);
		});

	auto cube_mesh = std::make_shared<Mesh>(std::string("res/assets/cube.obj"));
	add_object(std::make_unique<TestMesh>(cube_mesh, glm::mat4(1.0f)));
}

void Scene::draw() const {

	player->draw(cam.get_view_matrix(get_player_position()), proj);

	for (auto& obj : objects) {
		obj->draw(cam.get_view_matrix(get_player_position()), proj);
	}
}

void Scene::update(float delta) {

	player->update(delta, *this);

	for (auto& obj : objects) {
		if (auto* dynamic = dynamic_cast<DynamicObject*>(obj.get())) {
			dynamic->update(delta, *this);
		}
	}

	cam.update(delta, *this);
}

void Scene::add_object(std::unique_ptr<SceneObject> obj) {
	objects.push_back(std::move(obj));
}

const Camera Scene::get_camera() const { return cam; }

GLFWwindow& Scene::get_window() const { return window; }

const glm::vec3 Scene::get_player_position() const { return player->get_position(); }