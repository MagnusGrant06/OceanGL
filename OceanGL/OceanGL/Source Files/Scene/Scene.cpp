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

	setup_scene();
}

//setup actual values / objects / lights in scene, currently hardcoded for test objs and lights
void Scene::setup_scene() {

	lights.push_back(std::make_unique<PointLight>(
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.2f, 1.0f, 1.0f), 0.09f, 0.032f));
	lights.push_back(std::make_unique<PointLight>(
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.2f, -1.0f, 1.0f), 0.09f, 0.032f));

	//lights.push_back(std::make_unique<DirectionalLight>(
	//	glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
	//	glm::vec3(-0.2f, -1.0f, -0.3f)));

	lights.push_back(std::make_unique<DirectionalLight>(
		glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f),
		glm::vec3(3, -1, 4)
	));

	auto default_shader = std::make_shared<Shader>("default_vert.glsl", "default_frag.glsl");

	auto cube_mesh = std::make_shared<Mesh>(std::string("cube.obj"), default_shader);

	auto plane_mesh = std::make_shared<Mesh>(std::string("plane.obj"), default_shader);



	glm::mat4 plane_model = glm::mat4(1.0);

	plane_model = glm::translate(plane_model, glm::vec3(0, 15.0, 0.0));
	plane_model = glm::scale(plane_model, glm::vec3(100.0f));
	add_object(std::make_unique<TestMesh>(plane_mesh, plane_model, Material(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102), glm::vec3(0.297254f, 0.30829f, 0.306678), 0.1)));

	add_object(std::make_unique<TestMesh>(cube_mesh, glm::mat4(1.0f), Material(glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 700.0f)));

}
void Scene::draw() const {

	player->draw(cam.get_view_matrix(get_player_position()), proj, cam.get_cam_pos());
	for (auto& light : lights) {
		light->update(player->get_mesh().get_shader());
	}

	for (auto& obj : objects) {
		obj->draw(cam.get_view_matrix(get_player_position()), proj, cam.get_cam_pos());
		for (auto& light : lights) {
			light->update(obj->get_mesh().get_shader());
		}

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

const Light& Scene::get_light() const { return light; }