#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
struct GLFWwindow_deleter {

    void operator()(GLFWwindow* window) {
        glfwDestroyWindow(window);
    }
};

using GLFWwindow_ptr = std::unique_ptr<GLFWwindow, GLFWwindow_deleter>;

class Renderer {
public:

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    int render_window();
private:

};