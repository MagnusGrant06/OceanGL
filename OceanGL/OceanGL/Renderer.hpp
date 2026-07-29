#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>

#include "GLFWDeleter.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

class Renderer {
public:

    //used as function pointer to edit window size
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    int render_window();
private:

};