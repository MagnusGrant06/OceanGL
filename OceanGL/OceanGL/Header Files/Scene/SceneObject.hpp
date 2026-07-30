#include <glm/glm.hpp>

#include "Mesh.hpp"

class SceneObject {
protected:
	Mesh mesh;
	glm::mat4 model_matrix;

	SceneObject(Mesh mesh, glm::mat4 model_matrix) : mesh(std::move(mesh)), model_matrix(model_matrix) {};
public:
	virtual ~SceneObject() = default;
	virtual void draw() const = 0;
	virtual const glm::mat4& get_model_matrix() const = 0;
};