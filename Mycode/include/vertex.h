#ifndef __VERTEX_H__
#define __VERTEX_H__
#include "GL/glew.h"
#include "glm/glm.hpp"

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

	Vertex(glm::vec3 pos, glm::vec3 norm) : Vertex(pos, norm, {0,0}) {}
};
#endif // !__VERTEX_H__