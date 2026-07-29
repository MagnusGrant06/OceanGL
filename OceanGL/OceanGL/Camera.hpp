#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 cam_pos;
	glm::vec3 cam_front;
	glm::vec3 up_vec;

	bool first_mouse = true;
	float last_x = 400.0f;
	float last_y = 300.0f;

	float yaw = -90.0f;
	float pitch = 45.0f;


	glm::vec3 calculate_direction(float cam_yaw, float cam_pitch);

public:
	Camera();
	
	void process_input(GLFWwindow* window, float delta);

	void process_mouse_input(double xpos, double ypos);

	glm::mat4 get_view_matrix();

};