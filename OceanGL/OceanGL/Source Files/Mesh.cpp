#include "Mesh.hpp"


Mesh::Mesh(const std::string& filepath) {
	load_from_file(filepath);
	build_mesh_object();
	shader = std::make_shared<Shader>();
}

Mesh::Mesh(const std::string& filepath, std::shared_ptr<Shader> shader) : shader(std::move(shader)) {
	load_from_file(filepath);
	build_mesh_object();
}

Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<int> indices, std::shared_ptr<Shader> shader) : vertices(vertices), indices(indices), shader(std::move(shader)) {
	build_mesh_object();
}


void Mesh::load_from_file(const std::string& filepath) {
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;

	std::vector<int> temp_indices;
	std::ifstream file(FILE_PREFIX + filepath);
	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << filepath << std::endl;
	}
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
			std::vector<std::pair<int, int>> face_vertices;

			std::string triplet;
			while (stringStream >> triplet) {
				std::istringstream tripletStream(triplet);
				std::string token;
				std::vector<std::string> parts;

				while (std::getline(tripletStream, token, '/')) {
					parts.push_back(token);
				}

				int pos_index = std::stoi(parts[0]) - 1;
				int norm_index = -1;
				if (parts.size() >= 3 && !parts[2].empty())
					norm_index = std::stoi(parts[2]) - 1;

				face_vertices.push_back({ pos_index, norm_index });
			}

			//fan-triangulate
			for (size_t i = 1; i + 1 < face_vertices.size(); ++i) {
				auto add_vertex = [&](const std::pair<int, int>& v) {
					glm::vec3 normal = (v.second >= 0) ? temp_normals[v.second] : glm::vec3(0.0f, 1.0f, 0.0f);
					vertices.push_back(Vertex(temp_positions[v.first], normal));
					indices.push_back(static_cast<int>(vertices.size()) - 1);
					};

				add_vertex(face_vertices[0]);
				add_vertex(face_vertices[i]);
				add_vertex(face_vertices[i + 1]);
			}

		}
		else {
			continue;
		}
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


Mesh::Mesh(Mesh&& other) noexcept : shader(std::move(other.shader)), vertices(other.vertices), indices(other.indices), vbo(other.vbo), vao(other.vao), ibo(other.ibo) {
	other.vbo = 0;
	other.vao = 0;
	other.ibo = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {

	if (this != &other) {

		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);

		vbo = other.vbo;
		vao = other.vao;
		ibo = other.ibo;

		other.vbo = 0;
		other.vao = 0;
		other.ibo = 0;

	}

	return *this;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	vao = 0;
}

void Mesh::draw_mesh() const{
	if (vao == 0) return;

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

const Shader& Mesh::get_shader() const {
	return *shader;
}

void Mesh::printMeshData() {
	for (int index : indices) {
		std::cout << "Index: " << index << std::endl;
	}
	for (Vertex& v : vertices) {
		std::cout << "Vertex Position: " << v.position.x << ", " << v.position.y << ", " << v.position.z << std::endl;
		std::cout << "Vertex Normal: " << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << std::endl;
	}
}