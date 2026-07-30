#include "DynamicObject.hpp"

class PlayerCharacter : public DynamicObject {

public:

	PlayerCharacter(Mesh mesh, glm::mat4 model_matrix);

	void draw(glm::mat4 view, glm::mat4 proj) const;

	void update(float delta);

};