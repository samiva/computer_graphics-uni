#ifndef __ASSIGNMENT3_H__
#define __ASSIGNMENT3_H__
#include "cg-sources/scene.h"
#include "cg-sources/shaderprogram.h"
#include "cg-sources/texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include <vector>

class Assignment_3 : public Scene {

	struct Vertex {
		GLfloat position[3];
		GLfloat normal[3];
		GLfloat texcoord[2];

		Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex) {
			position[0] = pos.x;
			position[1] = pos.y;
			position[2] = pos.z;

			normal[0] = norm.x;
			normal[1] = norm.y;
			normal[2] = norm.z;

			texcoord[0] = tex.x;
			texcoord[1] = tex.y;
		}
	};

public:
	Assignment_3();
	// Inherited via Scene
	virtual bool init() override;
	virtual void resize(GLsizei width, GLsizei height) override;
	virtual void update(float timestep) override;
	virtual void render() override;
	virtual bool handleEvent(const SDL_Event & e) override;

private:
	ShaderProgram m_shaderCube;
	ShaderProgram m_shaderSkybox;

	Camera m_camera;

	glm::mat4 m_model;

	GLuint m_vaoCube, m_vboCube, m_eboCube;
	GLuint m_vaoSkybox, m_vboSkybox, m_eboSkyBox;

	// Textures
	GLuint m_skyboxCubeMap;
	GLuint m_skyboxTextureUnit = 0;

	std::vector<Vertex> m_cubeVertices;
	std::vector<unsigned int> m_cubeIndices;

	std::vector<Vertex> m_skyboxVertices;
	std::vector<unsigned int> m_skyboxIndices;
	
	void createCube();
	void createCubeMap(std::vector<std::string> filePaths);

	void mouseMotion();
};



#endif // !__ASSIGNMENT3_H__