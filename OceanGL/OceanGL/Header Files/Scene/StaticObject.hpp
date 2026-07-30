#include "SceneObject.hpp"

class StaticObject : public SceneObject {
protected:
	StaticObject(Mesh mesh, const glm::mat4 model);
public:
	virtual const glm::mat4& SceneObject::get_model_matrix() const override;
		
};