#include <vector>
#include <glad/glad.h>
#include <string>
#include <iostream>

#include "Shader.hpp"

class MeshCreator {

public:
	GLuint VAO, shader_program;


	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	

	int create_triangle();

	void draw_triangle();


private:

	
};