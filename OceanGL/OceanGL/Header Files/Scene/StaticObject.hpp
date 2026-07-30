#include "SceneObject.hpp"

//derived class for objects that will never interact with physics, that is their model matrix will never change
class StaticObject : public SceneObject {
protected:
	StaticObject(Mesh mesh, const glm::mat4 model);
public:
	virtual const glm::mat4& SceneObject::get_model_matrix() const override;
		
};