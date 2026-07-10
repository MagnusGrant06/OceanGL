// OceanGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
int main()
{
	std::unique_ptr<Renderer> renderer;

	if (!renderer->render_window()) {
		std::cout << "Could not initialize window" << std::endl;
		return -1;
	}

	return 0;
}

