#ifndef __MONKEY_SCENE_H__
#define __MONKEY_SCENE_H__
#include "cg-sources/scene.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "cg-sources/shaderprogram.h"
#include "cg-sources/objparser.h"
#include "vertex.h"
#include "cube.h"
#include <vector>

class MonkeyScene : Scene {
private:
	//struct Vertex
	//{
	//	GLfloat position[3];
	//	GLfloat normal[3];
	//	//GLfloat color[3];

	//	Vertex(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0, GLfloat nx = 0.0f, GLfloat ny = 0.0f, GLfloat nz = 0.0f)
	//	{
	//		position[0] = x;
	//		position[1] = y;
	//		position[2] = z;
	//		
	//		normal[0] = nx;
	//		normal[1] = ny;
	//		normal[2] = nz;
	//		
	//	}
	//};

	std::vector<Vertex> m_cubeVertices;
	std::vector<unsigned int> m_cubeIndices;
	ObjParser m_obj;

	Cube m_cube;


	ShaderProgram shaderProgram;
	glm::mat4 mvpMat;

	glm::mat4 projectionMat;
	glm::mat4 viewMat;
	glm::vec3 m_viewPos;

	float m_yaw = 0;
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	float m_posZ = 0.0f;
	float m_counter = 0.0f;
	// Vertex Array Object and Vertex Buffer Object handlers, elementbuffer
	GLuint vao, vbo ,ebo;

	void loadMonkey();
public:
	MonkeyScene();
	virtual ~MonkeyScene() override;
	virtual bool init() override;
	virtual void resize(GLsizei width, GLsizei height) override;
	virtual void update(float timestep) override;
	virtual void render() override;
	virtual bool handleEvent(const SDL_Event& e) override;
};
#endif //!__MONKEY_SCENE_H__