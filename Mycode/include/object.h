#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <GL/glew.h>
#include <vector>
#include "vertex.h"


class Object {
public:
	Object() {};
	virtual ~Object() {};
	virtual void create() = 0;
protected:
	GLuint m_vaoCube, m_vboCube, m_eboCube;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
#endif // !__OBJECT_H__