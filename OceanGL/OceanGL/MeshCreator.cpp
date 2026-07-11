#include "MeshCreator.hpp"

int MeshCreator::create_triangle() {
	Shader shader(std::string("res/shaders/default_vert.glsl"), std::string("res/shaders/default_frag.glsl"));
	shader_program = shader.shader_id;

	//generate initial vbo and vao objects
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	//bind vertex data to vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 1;

}

void MeshCreator::draw_triangle() {
	if (VAO == 0) return;

	glUseProgram(shader_program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}