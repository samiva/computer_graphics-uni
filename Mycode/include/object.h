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
	virtual void update(float dt) = 0;
	inline unsigned int getIndiceCount() { return m_indices.size(); }

	// Transform
	virtual glm::mat4& getModel() { return m_model; }
	virtual void rotate(const glm::vec3& rotation);
	virtual void translate(const glm::vec3& pos);
	virtual void scale(const glm::vec3& scale);

	void setMove(const glm::vec3& dir);
	void setRotation(const glm::vec3& axis);

	static glm::vec3 ZERO_VECTOR3;

	// Transform getters
	inline const glm::vec3& getPosition() { return m_position; }
	inline const glm::vec3& getRotation() { return m_rotation; }
	inline const glm::vec3& getScale() { return m_scale; }

	const glm::mat4 getLocalTransform();
	const glm::mat4 getGlobalTransform();

protected:
	GLuint m_vao, m_vbo, m_ebo;
	GLuint m_id;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	// Transform
	glm::mat4 m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale{ 1,1,1 };

	glm::vec3 m_moveDir;
	glm::vec3 m_rotAxis;
};
#endif // !__OBJECT_H__