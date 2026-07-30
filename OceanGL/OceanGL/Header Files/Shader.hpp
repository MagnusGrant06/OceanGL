#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
private:

	//default built in shaders 
	const std::string default_vertex_shader = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aNormal;\n"

		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"

		"void main()\n"
		"{\n"
		"   gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const std::string default_fragment_shader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	

	GLuint create_shader_program(const std::string& vertex_shader, const std::string& fragment_shader);
public:

	GLuint shader_id;

	Shader();

	Shader(std::string vert_filepath, std::string frag_filepath);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&&) noexcept;

	~Shader();

	
	void set_mat4(const std::string& name, const glm::mat4& mat) const;

	void use() const;
	
};