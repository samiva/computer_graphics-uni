#ifndef __CAMERA_H__ 
#define __CAMERA_H__
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Camera {
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 target);

	glm::mat4 getView();
	inline glm::mat4 getProj() { return m_proj; }
	inline void setMoveVertical(float factor) {  m_moveVertical = factor; }
	inline void setMoveHorizontal(float factor) { m_moveHorizontal = factor; }
	inline void setRotationYaw(float factor) { m_yawFactor = factor; }
	inline void setRotationPitch(float factor) { m_pitchFactor = factor; }
	void rotYaw(float factor);
	void rotPitch(float factor);
	void rotate(float yaw, float pitch);
	void setupProjection(float fovy, float aspect, float nearPlane, float farPlane);

	void update(float dt);

private:
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::vec3 m_left;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	float m_moveSpeed{ 10.0f };
	float m_moveVertical{ 0.0f };
	float m_moveHorizontal{ 0.0f };

	float m_yawFactor = 0.0f;
	float m_pitchFactor = 0.0f;
	float m_rotSpeed{ 2.0f };
	float m_yaw{ -90.0f };
	float m_pitch{ 0.0f };

	void calculateForward(glm::vec3 target);
	void calculateForward();
	void calculateLeft();
	void calculateUp();
	void updateVectors();

	void moveVertical(float factor);
	void moveHorizontal(float factor);
};
#endif // !__CAMERA_H__