#include "Renderer.hpp"

#include <iostream>


int Renderer::render_window() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow_ptr window(glfwCreateWindow(800, 600, "OceanGL", NULL, NULL));

    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to intialize GLAD" << std::endl;
        return 0;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

    while (!glfwWindowShouldClose(window.get())) {
        glfwSwapBuffers(window.get());
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 1;
}