#include "Shader.hpp"

//default constructor using pre-defined frag and vert shaders
Shader::Shader() {
	shader_program = create_shader_program(default_vertex_shader, default_fragment_shader);
}


GLuint Shader::create_shader_program(const std::string& vertex_shader_source, const std::string& fragment_shader_source) {
	GLuint shader;

	//load vertex shader into uint 
	GLuint vertex_shader;
	const char* raw_vert_source = vertex_shader_source.c_str();

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &raw_vert_source, NULL);
	glCompileShader(vertex_shader);

	//log any erroneous behaviour when compiling vertex shader
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "Vertex Shader Compilation failed: \n" << info_log << std::endl;
	}

	//load fragment shader into uint
	GLuint fragment_shader;
	const char* raw_frag_source = fragment_shader_source.c_str();
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &raw_frag_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	//log any erroneous behaviour when compiling fragment shader
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "Fragment Shader Compilation failed: \n" << info_log << std::endl;
	}

	//attach frag and vert and link final shader object
	shader = glCreateProgram();

	glAttachShader(shader, vertex_shader);
	glAttachShader(shader, fragment_shader);
	glLinkProgram(shader);

	//log any erroneous behaviour when linking shaders
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, info_log);
		std::cout << "Shader Linking failed: \n" << info_log << std::endl;
	}

	//clean up and delete dangling shader objects
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader;
}