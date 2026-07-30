#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>

#include "GLFWDeleter.hpp"
#include "Camera.hpp"
#include "Scene/PlayerCharacter.hpp"

class Renderer {
public:

    //used as function pointer to edit window size
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    int render_window();
private:

    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    glm::mat4 proj = glm::perspective(
        glm::radians(90.0f),
        static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
        0.1f,
        100.0f
    );

};