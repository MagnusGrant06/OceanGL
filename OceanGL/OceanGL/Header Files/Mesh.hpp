#pragma once

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
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ibo = 0;

	std::shared_ptr<Shader> shader;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	void load_from_file(const std::string& filename);

	void build_mesh_object();
public:

	Mesh(const std::string& filename);

	Mesh(const std::string& filename, std::shared_ptr<Shader> shader);

	Mesh(const std::vector<Vertex> vertices, const std::vector<int> indices, std::shared_ptr<Shader> shader);

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&&) noexcept;

	~Mesh();

	const Shader& get_shader() const;

	void draw_mesh() const;

	void printMeshData();
};