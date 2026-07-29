#include <vector>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "Shader.hpp"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};

class Mesh {

private:
	GLuint vao, vbo, ibo = 0;

	Shader shader;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	void load_from_file(const std::string& filename);

	void build_mesh_object();
public:

	Mesh(const std::string& filename);

	Mesh(const std::string& filename, Shader shader);

	~Mesh();

	Shader& get_shader();

	glm::mat4 get_model_matrix();

	void draw_mesh();

	void printMeshData();
};