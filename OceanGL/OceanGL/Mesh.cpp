#include "Mesh.hpp"


Mesh::Mesh(const std::string& filepath) {
	load_from_file(filepath);
	build_mesh_object();
	shader = Shader();
}

Mesh::Mesh(const std::string& filepath, Shader shader) : shader(std::move(shader)) {
	load_from_file(filepath);
	build_mesh_object();
}


void Mesh::load_from_file(const std::string& filepath) {
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;

	std::vector<int> temp_indices;
	std::ifstream file(filepath);
	std::string currentLine;

	while (std::getline(file, currentLine)) {

		std::istringstream stringStream(currentLine);
		std::string str;

		stringStream >> str;

		//load vertex positions from file into temporary vector
		if (str == "v") {
			float v1, v2, v3;
			stringStream >> v1 >> v2 >> v3;
			temp_positions.push_back(glm::vec3(v1, v2, v3));
		}

		//load vertex normals from file into temporary vector
		else if (str == "vn") {
			float v1, v2, v3;
			stringStream >> v1 >> v2 >> v3;
			temp_normals.push_back(glm::vec3(v1, v2, v3));

		}
		//load face information into temporary vector
		else if (str == "f") {
			std::string triplet;
			while (stringStream >> triplet) {
				std::istringstream tripletStream(triplet);
				std::string token;

				while (std::getline(tripletStream, token, '/')) {
					temp_indices.push_back(std::stoi(token) - 1);
				}
			}

		}
		else {
			continue;
		}
	}

	//loop through temp lists and create list of vertex to lookup in build
	for (int i = 0; i < temp_indices.size() - 2; i += 3) {
		vertices.push_back(Vertex(temp_positions[temp_indices[i]], temp_normals[temp_indices[i + 2]]));
		indices.push_back(vertices.size() - 1);
	}
}

void Mesh::build_mesh_object() {
	if (vao != 0) return;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	//use one vbo storing all my custom vector objects
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//tell opengl how to step through my vertex struct with these lines
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	vao = 0;
}

void Mesh::draw_mesh() {
	if (vao == 0) return;

	shader.use();

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Shader& Mesh::get_shader() {
	return shader;
}

glm::mat4 Mesh::get_model_matrix() {
	glm::mat4 model = glm::mat4(1.0f);
	return model;
}

void Mesh::printMeshData() {
	for (int index : indices) {
		std::cout << "Index: " << index << std::endl;
	}
	for (Vertex v : vertices) {
		std::cout << "Vertex Position: " << v.position.x << ", " << v.position.y << ", " << v.position.z << std::endl;
		std::cout << "Vertex Normal: " << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << std::endl;
	}
}