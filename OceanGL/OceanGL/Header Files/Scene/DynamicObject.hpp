#pragma once

#include "SceneObject.hpp"

class Scene;

//derived class where they interact with physics, and their model matrix changes 
class DynamicObject : public SceneObject {

protected:
	DynamicObject(std::shared_ptr<Mesh> mesh, const glm::mat4 initial_model);
public:
	virtual void update(float delta, Scene& scene) = 0;
	virtual const glm::mat4& get_model_matrix() const override;
};