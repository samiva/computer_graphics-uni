#include "../include/cube.h"
#include "../include/helpers.h"
#include <iostream>

void Cube::create() {
	//// Front
	//m_vertices.push_back(Vertex({ -1.0f,1.0f, 1.0f },  { 0,0,1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f,-1.0f, 1.0f }, { 0,0,1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,-1.0f, 1.0f }, { 0,0,1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,1.0f, 1.0f },  { 0,0,1.0f }, { 0,0 }));

	//// Back
	//m_vertices.push_back(Vertex({ -1.0f,1.0f,  -1.0f }, { 0,0,-1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f,-1.0f, -1.0f }, { 0,0,-1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,-1.0f,  -1.0f },{ 0,0,-1.0f }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,1.0f,   -1.0f },{ 0,0,-1.0f }, { 0,0 }));

	//// Right
	//m_vertices.push_back(Vertex({ 1.0f,  1.0f,  1.0f }, { 1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ 1.0f, -1.0f,  1.0f }, { 1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ 1.0f, -1.0f, -1.0f }, { 1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ 1.0f,  1.0f, -1.0f }, { 1.0f,0,0 }, { 0,0 }));

	//// Left
	//m_vertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { -1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { -1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { -1.0f,0,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { -1.0f,0,0 }, { 0,0 }));

	//// Top
	//m_vertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { 0,1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { 0,1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,  1.0f,  1.0f }, { 0,1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f,  1.0f, -1.0f }, { 0,1.0f,0 }, { 0,0 }));

	//// Bottom
	//m_vertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { 0,-1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { 0,-1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f, -1.0f, -1.0f }, { 0,-1.0f,0 }, { 0,0 }));
	//m_vertices.push_back(Vertex({  1.0f, -1.0f,  1.0f }, { 0,-1.0f,0 }, { 0,0 }));

	//// indices
	//// Front
	//m_indices.push_back(0);
	//m_indices.push_back(1);
	//m_indices.push_back(2);
	//m_indices.push_back(0);
	//m_indices.push_back(2);
	//m_indices.push_back(3);
	//// Back
	//m_indices.push_back(4);
	//m_indices.push_back(7);
	//m_indices.push_back(6);
	//m_indices.push_back(4);
	//m_indices.push_back(6);
	//m_indices.push_back(5);
	//// Right
	//m_indices.push_back(8);
	//m_indices.push_back(9);
	//m_indices.push_back(10);
	//m_indices.push_back(8);
	//m_indices.push_back(10);
	//m_indices.push_back(11);
	//// Left
	//m_indices.push_back(12);
	//m_indices.push_back(13);
	//m_indices.push_back(14);
	//m_indices.push_back(12);
	//m_indices.push_back(14);
	//m_indices.push_back(15);
	//// Top
	//m_indices.push_back(16);
	//m_indices.push_back(17);
	//m_indices.push_back(18);
	//m_indices.push_back(16);
	//m_indices.push_back(18);
	//m_indices.push_back(19);
	//// Bottom
	//m_indices.push_back(20);
	//m_indices.push_back(21);
	//m_indices.push_back(22);
	//m_indices.push_back(20);
	//m_indices.push_back(22);
	//m_indices.push_back(23);
	loadModel("cube.obj", m_vertices, m_indices);
	glCreateVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vertex),&m_vertices[0],GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int),&m_indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glVertexAttribPointer(2,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,normal)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Cube::bind()
{
	glBindVertexArray(m_vao);
	//glEnableVertexAttribArray(0);
}

void Cube::unbind()
{
	glBindVertexArray(0);
	//glDisableVertexAttribArray(0);
}

void Cube::update(float dt)
{
	
	//bool kakka = glm::all(glm::notEqual(m_moveDir, glm::vec3(0.0f)));
	if (glm::length(m_moveDir)!=0.0f) {
		m_position += m_moveDir*dt*10.0f;
		updateModel();
	}
	if (glm::length(m_rotAxis)!=0.0f) {
		m_rotation += m_rotAxis * dt*5.0f;
		updateModel();
	}
}

void Cube::updateModel()
{
	m_model = getGlobalTransform();
}
