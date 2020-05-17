#ifndef __ASSIGNMENT2_H__
#define __ASSIGNMENT2_H__
#include "cg-sources/scene.h"
#include "cg-sources/shaderprogram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector> 

class Texture;

class Assignment_2 : public Scene
{
private:
	struct Vertex {
		GLfloat position[3];
		GLfloat color[3];
		GLfloat normal[3];
		GLfloat texcoords[2];
		Vertex(GLfloat posx , GLfloat posy , GLfloat posz ,
			GLfloat r , GLfloat b , GLfloat g ,
			GLfloat nx, GLfloat ny , GLfloat nz )
		{
			position[0] = posx;
			position[1] = posy;
			position[2] = posz;
			
			color[0] = r;
			color[1] = b;
			color[2] = g;

			normal[0] = nx;
			normal[1] = ny;
			normal[2] = nz;
		}
		Vertex(GLfloat posx, GLfloat posy, GLfloat posz, 
			GLfloat uvx, GLfloat uvy) 
			: Vertex(posx,posy,posz, 0,0,0, 0,0,0) {
			texcoords[0] = uvx;
			texcoords[1] = uvy;
		}
	};
	std::vector<Vertex> m_cubeVertices;
	std::vector<unsigned int> m_cubeIndices;

	ShaderProgram m_shaderCube;
	Texture *m_texture = nullptr;
	GLuint m_textureUnit = 0;

	GLuint m_vaoCube, m_vboCube, m_eboCube;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	glm::mat4 m_model;

	glm::vec3 m_camPos;
	int m_moveFactor=0;
	int m_yawFactor = 0;
	int m_pitchFactor = 0;
	int m_speed = 5;

	float m_yaw=0, m_pitch=0;

	void createStuff();


public:
	Assignment_2();
	virtual ~Assignment_2();

	// Inherited via Scene
	virtual bool init() override;
	virtual void resize(GLsizei width, GLsizei height) override;
	virtual void update(float timestep) override;
	virtual void render() override;
	virtual bool handleEvent(const SDL_Event & e) override;
};
#endif // !__ASSIGNMENT2_H__