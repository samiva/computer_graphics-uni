#include "../include/Assignment2.h"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "cg-sources/texture.h"

void Assignment_2::createStuff()
{
	// vertices

	m_cubeVertices.push_back(Vertex(-1, 1, 1,  0.0f/3.0f, 3.0f/3.0f)); // Front
	m_cubeVertices.push_back(Vertex(-1, -1, 1,  0.0f/3.0f, 2.0f/3.0f));
	m_cubeVertices.push_back(Vertex(1, -1, 1,  1.0f/3.0f, 2.0f/3.0f));
	m_cubeVertices.push_back(Vertex(1, 1, 1,  1.0f/3.0f, 3.0f/3.0f));

	m_cubeVertices.push_back(Vertex(-1, 1, -1, 2.0f/3.0f, 2.0f/3.0f )); // Back
	m_cubeVertices.push_back(Vertex(-1, -1, -1, 2.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, -1, -1, 3.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, 1, -1, 3.0f / 3.0f, 2.0f / 3.0f));

	m_cubeVertices.push_back(Vertex(1, 1, 1, 1.0f / 3.0f, 3.0f / 3.0f)); // Right
	m_cubeVertices.push_back(Vertex(1, -1, 1, 1.0f / 3.0f, 2.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, -1, -1, 2.0f / 3.0f, 2.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, 1, -1, 2.0f / 3.0f, 3.0f / 3.0f));

	m_cubeVertices.push_back(Vertex(-1, 1, -1, 1.0f / 3.0f, 2.0f / 3.0f)); // Left
	m_cubeVertices.push_back(Vertex(-1, -1, -1, 1.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(-1, -1, 1, 2.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(-1, 1, 1, 2.0f / 3.0f, 2.0f / 3.0f));

	m_cubeVertices.push_back(Vertex(-1, 1, -1, 2.0f / 3.0f, 3.0f / 3.0f)); // Top
	m_cubeVertices.push_back(Vertex(-1, 1, 1, 2.0f / 3.0f, 2.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, 1, 1, 3.0f / 3.0f, 2.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, 1, -1, 3.0f / 3.0f, 3.0f / 3.0f));

	m_cubeVertices.push_back(Vertex(-1,-1, 1,  0.0f / 3.0f, 2.0f / 3.0f)); // Bottom
	m_cubeVertices.push_back(Vertex(-1,-1, -1, 0.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, -1, -1, 1.0f / 3.0f, 1.0f / 3.0f));
	m_cubeVertices.push_back(Vertex(1, -1, 1, 1.0f / 3.0f, 2.0f / 3.0f));

	// indices
	// Front
	m_cubeIndices.push_back(0);
	m_cubeIndices.push_back(1);
	m_cubeIndices.push_back(2);
	m_cubeIndices.push_back(0);
	m_cubeIndices.push_back(2);
	m_cubeIndices.push_back(3);
	// Back
	m_cubeIndices.push_back(4);
	m_cubeIndices.push_back(7);
	m_cubeIndices.push_back(6);
	m_cubeIndices.push_back(4);
	m_cubeIndices.push_back(6);
	m_cubeIndices.push_back(5);
	// Right
	m_cubeIndices.push_back(8);
	m_cubeIndices.push_back(9);
	m_cubeIndices.push_back(10);
	m_cubeIndices.push_back(8);
	m_cubeIndices.push_back(10);
	m_cubeIndices.push_back(11);
	// Left
	m_cubeIndices.push_back(12);
	m_cubeIndices.push_back(13);
	m_cubeIndices.push_back(14);
	m_cubeIndices.push_back(12);
	m_cubeIndices.push_back(14);
	m_cubeIndices.push_back(15);
	// Top
	m_cubeIndices.push_back(16);
	m_cubeIndices.push_back(17);
	m_cubeIndices.push_back(18);
	m_cubeIndices.push_back(16);
	m_cubeIndices.push_back(18);
	m_cubeIndices.push_back(19);
	// Bottom
	m_cubeIndices.push_back(20);
	m_cubeIndices.push_back(21);
	m_cubeIndices.push_back(22);
	m_cubeIndices.push_back(20);
	m_cubeIndices.push_back(22);
	m_cubeIndices.push_back(23);
	m_texture = new Texture("data/uvtemplate.png");
}

Assignment_2::Assignment_2()
{
	assert(glBindBuffer != 0);
	assert(glBindVertexArray != 0);
	assert(glBufferData != 0);
	assert(glClear != 0);
	assert(glClearColor != 0);
	assert(glCullFace != 0);
	assert(glDepthFunc != 0);
	assert(glDeleteBuffers != 0);
	assert(glDeleteVertexArrays != 0);
	assert(glDisableVertexAttribArray != 0);
	assert(glDrawArrays != 0);
	assert(glEnable != 0);
	assert(glGenVertexArrays != 0);
	assert(glGenBuffers != 0);
	assert(glUseProgram != 0);
	assert(glUniformMatrix4fv != 0);
	assert(glVertexAttribPointer != 0);
	assert(glViewport != 0);
}

Assignment_2::~Assignment_2()
{
	delete m_texture;
}

bool Assignment_2::init()
{
	createStuff();
	if (!m_shaderCube.load("data/assignment2.vs", "data/assignment2.fs"))
		return false;

	glUseProgram(m_shaderCube.getShaderProgram());

	GLint textureLocation = glGetUniformLocation(m_shaderCube.getShaderProgram(), "texture0");

	glUniform1i(textureLocation, m_textureUnit);


	// Enable stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndices.size() * sizeof(unsigned int), &m_cubeIndices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_cubeVertices.size() * sizeof(Vertex), &m_cubeVertices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(m_shaderCube.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glEnableVertexAttribArray(m_shaderCube.getPositionAttribLocation());

	glVertexAttribPointer(m_shaderCube.getColorAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
	glEnableVertexAttribArray(m_shaderCube.getColorAttribLocation());

	glVertexAttribPointer(m_shaderCube.getNormalAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(m_shaderCube.getNormalAttribLocation());

	glVertexAttribPointer(m_shaderCube.getTexture0AttribLocation(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texcoords)));
	glEnableVertexAttribArray(m_shaderCube.getTexture0AttribLocation());


	m_camPos = glm::vec3(0, 0, 3);

	m_view = glm::lookAt(m_camPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
	return true;
}

void Assignment_2::resize(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	float fovy = 45.0f;
	m_proj = glm::perspective(fovy, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

void Assignment_2::update(float timestep)
{
	if (m_moveFactor != 0) {
		m_camPos.z += m_moveFactor * m_speed * timestep;
	}
	if (m_yawFactor != 0) {
		m_yaw += m_yawFactor * m_speed * timestep;
	}if (m_pitchFactor != 0) {
		m_pitch += m_pitchFactor * m_speed * timestep;
	}
}

void Assignment_2::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_shaderCube.getShaderProgram());

	auto T = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	auto Ry = glm::rotate(glm::mat4(), m_yaw, glm::vec3(0, 1, 0));
	auto Rx = glm::rotate(glm::mat4(), m_pitch, glm::vec3(1, 0, 0));
	auto R = Rx * Ry;
	m_modelCube = T * R;
	m_view = glm::lookAt(m_camPos, glm::vec3(0), glm::vec3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_model"), 1, GL_FALSE, glm::value_ptr(m_modelCube));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_view"), 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_proj"), 1, GL_FALSE, glm::value_ptr(m_proj));
	glActiveTexture(GL_TEXTURE0 + m_textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_texture->getTextureId());
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_cubeIndices.size()), GL_UNSIGNED_INT, 0);
}

bool Assignment_2::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_EventType::SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			return false;
			break;
		case SDLK_s:case SDLK_w:
			m_moveFactor = 0;
			break;
		case SDLK_LEFT: case SDLK_RIGHT:
			m_yawFactor = 0;
			break;
		case SDLK_DOWN: case SDLK_UP:
			m_pitchFactor = 0;
			break;
		}
	}
	else if (e.type == SDL_EventType::SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_s:
			m_moveFactor = 1;
			break;
		case SDLK_w:
			m_moveFactor = -1;
			break;
		case SDLK_LEFT:
			m_yawFactor = -1;
			break;
		case SDLK_RIGHT:
			m_yawFactor = 1;
			break;
		case SDLK_UP:
			m_pitchFactor = -1;
			break;
		case SDLK_DOWN:
			m_pitchFactor = 1;
			break;
		}
	}
	return true;
}
