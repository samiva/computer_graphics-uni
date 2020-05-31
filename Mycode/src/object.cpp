#include "../include/object.h"
#include "GL/glew.h"

GLuint Object::idCounter = 0;
glm::vec3 Object::ZERO_VECTOR3 = glm::vec3{0.0f,0.0f,0.0f};

Object::Object() {
    m_id = idCounter;
    idCounter++;    
}

 Object::~Object() {}

 void Object::rotate(const glm::vec3 & rotation)
 {
	 m_rotation = rotation;
 }

 void Object::translate(const glm::vec3 & pos)
 {
	 m_position = pos;
 }

 void Object::scale(const glm::vec3 & scale)
 {
	 m_scale = scale;
 }

 void Object::setMove(const glm::vec3 & dir)
 {
	 m_moveDir = dir;
 }

 void Object::setRotation(const glm::vec3 & axis)
 {
	 m_rotAxis = axis;
 }

 const glm::mat4 Object::getLocalTransform()
 {
	 auto T = glm::translate(glm::mat4(), m_position);
	 auto Rz = glm::rotate(glm::mat4(), m_rotation.z, glm::vec3(0, 0, 1));
	 auto Ry = glm::rotate(glm::mat4(), m_rotation.y, glm::vec3(0, 1, 0));
	 auto Rx = glm::rotate(glm::mat4(), m_rotation.x, glm::vec3(1, 0, 0));
	 auto R = Rz * Ry*Rx;
	 auto S = glm::scale(glm::mat4(), m_scale);
	 return S * R*T;
 }

 const glm::mat4 Object::getGlobalTransform()
 {
	 auto T = glm::translate(glm::mat4(), m_position);
	 auto Rz = glm::rotate(glm::mat4(), m_rotation.z, glm::vec3(0, 0, 1));
	 auto Ry = glm::rotate(glm::mat4(), m_rotation.y, glm::vec3(0, 1, 0));
	 auto Rx = glm::rotate(glm::mat4(), m_rotation.x, glm::vec3(1, 0, 0));
	 auto R = Rz * Ry*Rx;
	 auto S = glm::scale(glm::mat4(), m_scale);

	 return T * R*S;
 }
