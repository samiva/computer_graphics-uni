#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <GL/glew.h>
#include <vector>
#include "vertex.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Object {
	static GLuint idCounter;
public:
	Object();
	virtual ~Object();
	virtual void create() = 0;
	virtual void bind()=0;
	virtual void unbind()=0;
	virtual glm::mat4& getModel() { return m_model; }
	virtual unsigned int getIndiceCount() { return m_indices.size(); }

protected:
	GLuint m_vao, m_vbo, m_ebo;
	GLuint m_id;
	glm::mat4 m_model;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
#endif // !__OBJECT_H__