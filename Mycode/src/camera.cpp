#include "../include/camera.h"

#include <iostream>

using glm::radians;
using glm::cos;
using glm::sin;

Camera::Camera() :Camera({ 0.0f,0.0f,10.0f }, {0.0f,0.0f,0.0f})
{
}

Camera::Camera(glm::vec3 position, glm::vec3 target) : m_position(position), m_up(glm::vec3(0.0f,1.0f,0.0f))
{
	calculateForward(target);
	calculateLeft();
	calculateUp();
}

glm::mat4 Camera::getView()
{
	auto target = m_position + m_forward * 10.0f;
	std::cout << "Camera {target: " << target.x << " " << target.y << " " << target.z << " up: " << m_up.x << " " << m_up.y << " " << m_up.z << std::endl;
	return glm::lookAt(m_position, target, m_up);
}



void Camera::rotate(float yaw, float pitch)
{

}

void Camera::setupProjection(float fovy, float aspect, float nearPlane, float farPlane)
{
	m_proj = glm::perspective(fovy, aspect, nearPlane, farPlane);
}

void Camera::update(float dt)
{
	// Positon update
	if (m_moveVertical != 0.0f) {
		moveVertical(m_moveVertical*dt);
	}
	if (m_moveHorizontal != 0.0f) {
		moveHorizontal(dt*m_moveHorizontal);
	}


	//Rotation update
	 //yaw
	if (m_yawFactor != 0.0f) {
		rotYaw(dt*m_yawFactor);
		
	}
	// Pitch
	if (m_pitchFactor != 0.0f) {
		rotPitch(dt*m_pitchFactor);
		
	}
	updateVectors();
	setRotationYaw(0);
	setRotationPitch(0);
}


void Camera::calculateForward(glm::vec3 target) 
{ 
	m_forward = glm::normalize(target - m_position); 
}

void Camera::calculateForward()
{
	m_forward = glm::normalize(glm::vec3(cos(m_yaw)*cos(m_pitch), sin(m_pitch), sin(m_yaw)*cos(m_pitch)));
}

void Camera::calculateLeft() 
{ 
	glm::vec3 up(0.0f,1.0,0.0f);
	m_left = (glm::normalize(glm::cross(m_forward, up))); 
}

void Camera::calculateUp()
{
	m_up = glm::normalize(glm::cross(m_left, m_forward));
}

void Camera::updateVectors()
{
	calculateForward();
	calculateLeft();
	
}

void Camera::moveVertical(float factor)
{
	m_position += m_forward * factor * m_moveSpeed;	
}

void Camera::moveHorizontal(float factor)
{
	m_position += m_left * factor * m_moveSpeed;	
}

void Camera::rotYaw(float factor)
{
	m_yaw += factor * m_rotSpeed;
	//if (m_yaw > 359.0f) {
	//	m_yaw=0.0f;
	//}
	//else if (m_yaw < 0.0f) {
	//	m_yaw = 359.0f;
	//}
	std::cout << "Yaw angle: " << m_yaw << std::endl;
}

void Camera::rotPitch(float factor)
{
	auto max = glm::quarter_pi<float>();
	auto min = -glm::quarter_pi<float>();
	m_pitch += factor * m_rotSpeed;
	//m_pitch = radians(m_pitch);
	m_pitch=glm::clamp(m_pitch, min,max);
	std::cout << "Pitch angle: " << m_pitch << std::endl;
}