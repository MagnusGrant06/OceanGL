#pragma once

#include "StaticObject.hpp"

class SkyBox : public StaticObject {
private:
	const std::string IMG_PATH = "res/assets/";

	GLuint cubemap_texture = 0;
public:

	SkyBox(std::shared_ptr<Mesh> mesh, glm::mat4 model, Material mat);
	
	GLuint load_cubemap(std::vector<std::string> img_paths);

	void draw(glm::mat4 view, glm::mat4 proj, glm::vec3 cam_pos) const override;

	const Mesh& get_mesh() const override { return *mesh; }
};