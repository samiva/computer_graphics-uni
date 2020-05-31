#ifndef __ASSIGNMENT3_H__
#define __ASSIGNMENT3_H__
#include "cg-sources/scene.h"
#include "cg-sources/shaderprogram.h"
#include "cg-sources/texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#include "vertex.h"
#include "../include/cube.h"
#include <vector>

class Assignment_3 : public Scene {

	

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
	ShaderProgram m_lightingShader;

	Camera m_camera;

	glm::mat4 m_modelCube;
	glm::mat4 m_modelCube2;
	glm::mat4 m_modelEarth;
	Cube m_sun;
	Cube m_mercurius;
	Cube m_earth;

	float m_yaw = 0;
	float m_roll = 0;

	GLuint m_vao, m_vbo, m_ebo;
	GLuint m_vaoCube2, m_vboCube2, m_eboCube2;
	GLuint m_vaoSkybox, m_vboSkybox, m_eboSkyBox;

	// Textures
	GLuint m_skyboxCubeMap;
	GLuint m_skyboxTextureUnit = 0;

	std::vector<Vertex> m_cubeVertices;
	std::vector<unsigned int> m_cubeIndices;

	std::vector<Vertex> m_cube2Vertices;
	std::vector<unsigned int> m_cube2Indices;

	std::vector<Vertex> m_skyboxVertices;
	std::vector<unsigned int> m_skyboxIndices;
	
	void createCube();
	void createCubeMap(std::vector<std::string> filePaths);

	void mouseMotion();
};



#endif // !__ASSIGNMENT3_H__