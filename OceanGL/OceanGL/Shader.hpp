#include <glad/glad.h>
#include <string>
#include <iostream>

class Shader {
private:
	const std::string default_vertex_shader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const std::string default_fragment_shader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	

	GLuint create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
public:

	GLuint shader_program;

	Shader();

	Shader(std::string filepath);


	
};