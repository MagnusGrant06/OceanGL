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
    PlayerCharacter player(std::move(shark_mesh), glm::mat4(1.0f));

    std::cout << "after creation " << glGetError() << std::endl;
    float delta_time = 0.0f;
    float last_frame = 0.0f;
    std::cout << "after drawing" << glGetError() << std::endl;
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

        player.update(delta_time);
        player.draw(camera.get_view_matrix(), proj);
       
        glfwSwapBuffers(window.get());
        glfwPollEvents();

    }
    std::cout << "after finishing " << glGetError() << std::endl;
    glfwTerminate();
    return 1;
}