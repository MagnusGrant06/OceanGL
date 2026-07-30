#pragma once

#include "DynamicObject.hpp"
#include "../Camera.hpp"

class PlayerCharacter : public DynamicObject {

public:

	PlayerCharacter(Mesh mesh, glm::mat4 model_matrix);

	void draw(glm::mat4 view, glm::mat4 proj) const override;

	void update(float delta, Scene& scene) override;

	glm::mat4 follow_camera(const Camera& cam);

};