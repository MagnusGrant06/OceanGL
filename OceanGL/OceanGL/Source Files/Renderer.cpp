#include "Renderer.hpp"

#include <iostream>


int Renderer::render_window() {

   // MeshCreator mesh;

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


    Camera camera;

    Mesh shark_mesh(std::string("res/assets/shark2f.obj"));

    float delta_time = 0.0f;
    float last_frame = 0.0f;

    //primary draw loop
    while (!glfwWindowShouldClose(window.get())) {
        
        //calculate physics process timings
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        camera.process_input(window.get(), delta_time);

        //accept mouse input
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetWindowUserPointer(window.get(), &camera);

        //small captureless lambda to use as function pointer to mouse input calcs
        glfwSetCursorPosCallback(window.get(), [](GLFWwindow* lambda_window, double xpos, double ypos) {
            auto* self = static_cast<Camera*>(glfwGetWindowUserPointer(lambda_window));
            self->process_mouse_input(xpos, ypos);
        });

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shark_mesh.get_shader().use();
        shark_mesh.get_shader().set_mat4("view", camera.get_view_matrix());
        shark_mesh.get_shader().set_mat4("proj", proj);
        shark_mesh.get_shader().set_mat4("model", glm::rotate(shark_mesh.get_model_matrix(), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0,0,1)));
        shark_mesh.draw_mesh();

        glfwSwapBuffers(window.get());
        glfwPollEvents();

    }
    std::cout << "after finishing " << glGetError() << std::endl;
    glfwTerminate();
    return 1;
}