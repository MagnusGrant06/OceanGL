#include "Scene/SkyBox.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stbi/stb_image.h"

SkyBox::SkyBox(std::shared_ptr<Mesh> mesh, glm::mat4 model, Material mat) : StaticObject(std::move(mesh), model, mat){
	
	std::vector<std::string> tex_locations = {
		IMG_PATH + "px.png",
		IMG_PATH + "nx.png",
		IMG_PATH + "py.png",
		IMG_PATH + "ny.png",
		IMG_PATH + "pz.png",
		IMG_PATH + "nz.png"
	};

	cubemap_texture = load_cubemap(tex_locations);

}

GLuint SkyBox::load_cubemap(std::vector<std::string> img_paths) {

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);


	int width, height, nrChannels;
	unsigned char* data;

	for (size_t i{}; i < img_paths.size(); ++i) {
		data = stbi_load(img_paths[i].c_str(), &width, &height, &nrChannels, 0);

		GLenum format = GL_RGB;
		if (nrChannels == 1)      format = GL_RED;
		else if (nrChannels == 4) format = GL_RGBA;

		if (data) {
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}

		else {
			std::cout << "Cubemap failed loading at path: " << img_paths[i] << std::endl;
			stbi_image_free(data);
		}

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void SkyBox::draw(glm::mat4 view, glm::mat4 proj, glm::vec3 cam_pos) const {
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);


	glm::mat4 adjusted_view = glm::mat4(glm::mat3(view));
	mesh->get_shader().use();
	mesh->get_shader().set_mat4("view", adjusted_view);
	mesh->get_shader().set_mat4("projection", proj);

	//mat.update(mesh->get_shader());
	
	glBindVertexArray(mesh->get_vao());
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

}