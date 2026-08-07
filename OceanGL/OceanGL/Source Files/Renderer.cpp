#include "Renderer.hpp"

#include <iostream>


int Renderer::render_window() {

    //create initial window context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //custom window ptr object to safely handle window creation and deletion
    GLFWwindow_ptr window(glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OceanGL", NULL, NULL));

    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to intialize GLAD" << std::endl;
        return 0;
    }

    //set size of viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    std::shared_ptr<Mesh> player_mesh = std::make_shared<Mesh>(std::string("res/assets/shark2f.obj"));
    Scene scene(proj, *window.get(), std::make_unique<PlayerCharacter>(player_mesh, glm::mat4(1.0f)));
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    //primary draw loop
    while (!glfwWindowShouldClose(window.get())) {
        //calculate physics process timings
        float current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(delta_time);
        scene.draw();

        glfwSwapBuffers(window.get());
        glfwPollEvents();

    }
    std::cout << "after finishing " << glGetError() << std::endl;
    glfwTerminate();
    return 1;
}