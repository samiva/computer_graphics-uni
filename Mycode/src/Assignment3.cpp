#include "../include/Assignment3.h"
#include "glm/gtc/type_ptr.hpp"
#include "../include/helpers.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

Assignment_3::Assignment_3()
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

bool Assignment_3::init()
{
	createCube();
	auto cubeShaders = getShaderPaths("BasicShader");
	if (!m_shaderCube.load(cubeShaders[0], cubeShaders[1])) {
		return false;
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	//// Cube
	//glGenVertexArrays(1, &m_vaoCube);
	//glBindVertexArray(m_vaoCube);

	//glGenBuffers(1, &m_vboCube);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vboCube);
	//glBufferData(GL_ARRAY_BUFFER, m_cubeVertices.size() * sizeof(Vertex), &m_cubeVertices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &m_eboCube);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboCube);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndices.size() * sizeof(unsigned int), &m_cubeIndices[0], GL_STATIC_DRAW);

	//glVertexAttribPointer(m_shaderCube.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	//glEnableVertexAttribArray(m_shaderCube.getPositionAttribLocation());

	//// Cube2
	//glGenVertexArrays(1, &m_vaoCube2);
	//glBindVertexArray(m_vaoCube2);

	//glGenBuffers(1, &m_vboCube2);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vboCube2);
	//glBufferData(GL_ARRAY_BUFFER, m_cube2Vertices.size() * sizeof(Vertex), &m_cube2Vertices[0], GL_STATIC_DRAW);

	//glGenBuffers(1, &m_eboCube2);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboCube2);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cube2Indices.size() * sizeof(unsigned int), &m_cube2Indices[0], GL_STATIC_DRAW);

	//glVertexAttribPointer(m_shaderCube.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	//glEnableVertexAttribArray(m_shaderCube.getPositionAttribLocation());

	// Skybox
	auto skyShaderPaths = getShaderPaths("SkyboxShader");
	if (!m_shaderSkybox.load(skyShaderPaths[0], skyShaderPaths[1])) {
		return false;
	}

	glGenVertexArrays(1, &m_vaoSkybox);
	glBindVertexArray(m_vaoSkybox);

	glGenBuffers(1, &m_vboSkybox);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboSkybox);
	glBufferData(GL_ARRAY_BUFFER, m_skyboxVertices.size()*sizeof(Vertex), &m_skyboxVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_eboSkyBox);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboSkyBox);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_skyboxIndices.size()*sizeof(unsigned int), &m_skyboxIndices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(m_shaderSkybox.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,position)));
	glEnableVertexAttribArray(m_shaderSkybox.getPositionAttribLocation());

	auto imgs = getSkyboxImages();
	createCubeMap(imgs);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(.1f, .3f, .1f, 1.0f);
	return true;
}

void Assignment_3::resize(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	float fovy = 45.0f;
	m_camera.setupProjection(fovy, static_cast<float>(width) / static_cast<float>(height), .1f, 1000.0f);

}

void Assignment_3::update(float timestep)
{
	m_camera.update(timestep);
}

void Assignment_3::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_shaderCube.getShaderProgram());

	auto T = glm::translate(glm::mat4(1.0f), { 0,0,0 });

	m_modelCube = T;
	auto V = m_camera.getView();
	auto P = m_camera.getProj();

	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_viewMat"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_modelMat"), 1, GL_FALSE, glm::value_ptr(m_modelCube));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_projMat"), 1, GL_FALSE, glm::value_ptr(P));

	//glBindVertexArray(m_vaoCube);
	m_cube.bind();
	glDrawElements(GL_TRIANGLES, m_cube.getIndiceCount() , GL_UNSIGNED_INT, 0);
	m_cube.unbind();
	// Draw cube2
	auto T2 = glm::translate(glm::mat4(), { -10, 0,0 });
	m_modelCube2 = T2;
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_viewMat"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_modelMat"), 1, GL_FALSE, glm::value_ptr(m_modelCube2));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderCube.getShaderProgram(), "_projMat"), 1, GL_FALSE, glm::value_ptr(P));

	m_cube2.bind();
	glDrawElements(GL_TRIANGLES, m_cube2.getIndiceCount(), GL_UNSIGNED_INT, 0);

	glUseProgram(m_shaderSkybox.getShaderProgram());

	auto M = /*glm::mat4(1.0F);*/ glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	V = glm::mat4(glm::mat3(V));
	auto MVP = P * V * M;
	glUniformMatrix4fv(glGetUniformLocation(m_shaderSkybox.getShaderProgram(), "_mvp"), 1, GL_FALSE, glm::value_ptr(MVP));
	auto skyboxTexLoc = glGetUniformLocation(m_shaderSkybox.getShaderProgram(),"_skyboxtex");
	if (skyboxTexLoc > -1) {
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glBindTextureUnit(0, m_skyboxCubeMap);
	}
	glBindVertexArray(m_vaoSkybox);
	//glDisable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_TRIANGLES, m_skyboxIndices.size(), GL_UNSIGNED_INT, 0	);
}

bool Assignment_3::handleEvent(const SDL_Event & e)
{
	//m_camera.setRotationYaw(0.0f);
	//m_camera.setRotationPitch(0.0f);
	if (e.type == SDL_EventType::SDL_MOUSEMOTION) {
		mouseMotion();
	}
	else if (e.type == SDL_EventType::SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			m_camera.setMoveVertical(1.0f);
			break;
		case SDLK_DOWN:
			m_camera.setMoveVertical(-1.0f);
			break;
		case SDLK_LEFT:
			m_camera.setMoveHorizontal(-1.0f);
			break;
		case SDLK_RIGHT:
			m_camera.setMoveHorizontal(1.0f);
			break;
		case SDLK_a:
			m_camera.setMoveHorizontal(-1.0f);
			//m_camera.setRotationYaw(-1.0f);
			//m_camera.rotYaw(-1.0f);
			break;
		case SDLK_d:
			m_camera.setMoveHorizontal(1.0f);
			//m_camera.setRotationYaw(1.0f);
			//m_camera.rotYaw(1.0);
			break;
		case SDLK_w:
			m_camera.setMoveVertical(1.0f);
			//m_camera.setRotationPitch(1.0f);
			//m_camera.rotPitch(1.0f);
			break;
		case SDLK_s:
			m_camera.setMoveVertical(-1.0f);
			//m_camera.setRotationPitch(-1.0f);
			//m_camera.rotPitch(-1.0f);
			break;
		
		case SDLK_ESCAPE:
			return false;
		}
	}
	else if (e.type == SDL_EventType::SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: case SDLK_DOWN:
			m_camera.setMoveVertical(0.0f);
			break;
		case SDLK_LEFT: case SDLK_RIGHT:
			m_camera.setMoveHorizontal(0.0f);
			break;
		case SDLK_a: case SDLK_d:
			m_camera.setMoveHorizontal(0.0f);
			//m_camera.setRotationYaw(0.0f);
			break;
		case SDLK_w: case SDLK_s:
			m_camera.setMoveVertical(0.0f);
			//m_camera.setRotationPitch(0.0f);
			break;
		}
	}

	return true;
}

void Assignment_3::createCube()
{
	m_cube.create();
	m_cube2.create();
	//// Front
	//m_cubeVertices.push_back(Vertex({ -1.0f,1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f,-1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,-1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));

	//// Back
	//m_cubeVertices.push_back(Vertex({ -1.0f,1.0f,  -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f,-1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,-1.0f,  -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,1.0f,   -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Right
	//m_cubeVertices.push_back(Vertex({ 1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Left
	//m_cubeVertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));

	//// Top
	//m_cubeVertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Bottom
	//m_cubeVertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cubeVertices.push_back(Vertex({ 1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));

	//// indices
	//// Front
	//m_cubeIndices.push_back(0);
	//m_cubeIndices.push_back(1);
	//m_cubeIndices.push_back(2);
	//m_cubeIndices.push_back(0);
	//m_cubeIndices.push_back(2);
	//m_cubeIndices.push_back(3);
	//// Back
	//m_cubeIndices.push_back(4);
	//m_cubeIndices.push_back(7);
	//m_cubeIndices.push_back(6);
	//m_cubeIndices.push_back(4);
	//m_cubeIndices.push_back(6);
	//m_cubeIndices.push_back(5);
	//// Right
	//m_cubeIndices.push_back(8);
	//m_cubeIndices.push_back(9);
	//m_cubeIndices.push_back(10);
	//m_cubeIndices.push_back(8);
	//m_cubeIndices.push_back(10);
	//m_cubeIndices.push_back(11);
	//// Left
	//m_cubeIndices.push_back(12);
	//m_cubeIndices.push_back(13);
	//m_cubeIndices.push_back(14);
	//m_cubeIndices.push_back(12);
	//m_cubeIndices.push_back(14);
	//m_cubeIndices.push_back(15);
	//// Top
	//m_cubeIndices.push_back(16);
	//m_cubeIndices.push_back(17);
	//m_cubeIndices.push_back(18);
	//m_cubeIndices.push_back(16);
	//m_cubeIndices.push_back(18);
	//m_cubeIndices.push_back(19);
	//// Bottom
	//m_cubeIndices.push_back(20);
	//m_cubeIndices.push_back(21);
	//m_cubeIndices.push_back(22);
	//m_cubeIndices.push_back(20);
	//m_cubeIndices.push_back(22);
	//m_cubeIndices.push_back(23);

	// Skybox
	// Front
	m_skyboxVertices.push_back(Vertex({ -10.0f,10.0f, 10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f,-10.0f, 10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,-10.0f, 10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,10.0f, 10.0f }, { 0,0,0 }, { 0,0 }));

	// Back
	m_skyboxVertices.push_back(Vertex({ -10.0f,10.0f,  -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f,-10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,-10.0f,  -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,10.0f,   -10.0f }, { 0,0,0 }, { 0,0 }));

	// Right
	m_skyboxVertices.push_back(Vertex({ 10.0f,  10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f, -10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f, -10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,  10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));

	// Left
	m_skyboxVertices.push_back(Vertex({ -10.0f,  10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f, -10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f, -10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f,  10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));

	// Top
	m_skyboxVertices.push_back(Vertex({ -10.0f,  10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f,  10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,  10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f,  10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));

	// Bottom
	m_skyboxVertices.push_back(Vertex({ -10.0f, -10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ -10.0f, -10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f, -10.0f, -10.0f }, { 0,0,0 }, { 0,0 }));
	m_skyboxVertices.push_back(Vertex({ 10.0f, -10.0f,  10.0f }, { 0,0,0 }, { 0,0 }));

	// indices
	// Front
	m_skyboxIndices.push_back(0);
	m_skyboxIndices.push_back(1);
	m_skyboxIndices.push_back(2);
	m_skyboxIndices.push_back(0);
	m_skyboxIndices.push_back(2);
	m_skyboxIndices.push_back(3);
	// Back
	m_skyboxIndices.push_back(4);
	m_skyboxIndices.push_back(7);
	m_skyboxIndices.push_back(6);
	m_skyboxIndices.push_back(4);
	m_skyboxIndices.push_back(6);
	m_skyboxIndices.push_back(5);
	// Right
	m_skyboxIndices.push_back(8);
	m_skyboxIndices.push_back(9);
	m_skyboxIndices.push_back(10);
	m_skyboxIndices.push_back(8);
	m_skyboxIndices.push_back(10);
	m_skyboxIndices.push_back(11);
	// Left
	m_skyboxIndices.push_back(12);
	m_skyboxIndices.push_back(13);
	m_skyboxIndices.push_back(14);
	m_skyboxIndices.push_back(12);
	m_skyboxIndices.push_back(14);
	m_skyboxIndices.push_back(15);
	// Top
	m_skyboxIndices.push_back(16);
	m_skyboxIndices.push_back(17);
	m_skyboxIndices.push_back(18);
	m_skyboxIndices.push_back(16);
	m_skyboxIndices.push_back(18);
	m_skyboxIndices.push_back(19);
	// Bottom
	m_skyboxIndices.push_back(20);
	m_skyboxIndices.push_back(21);
	m_skyboxIndices.push_back(22);
	m_skyboxIndices.push_back(20);
	m_skyboxIndices.push_back(22);
	m_skyboxIndices.push_back(23);


	// Cube 2
	// Front
	//m_cube2Vertices.push_back(Vertex({ -1.0f,1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f,-1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,-1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, { 0,0 }));

	//// Back
	//m_cube2Vertices.push_back(Vertex({ -1.0f,1.0f,  -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f,-1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,-1.0f,  -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,1.0f,   -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Right
	//m_cube2Vertices.push_back(Vertex({ 1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Left
	//m_cube2Vertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));

	//// Top
	//m_cube2Vertices.push_back(Vertex({ -1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,  1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f,  1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));

	//// Bottom
	//m_cube2Vertices.push_back(Vertex({ -1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ -1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f, -1.0f, -1.0f }, { 0,0,0 }, { 0,0 }));
	//m_cube2Vertices.push_back(Vertex({ 1.0f, -1.0f,  1.0f }, { 0,0,0 }, { 0,0 }));

	//// indices
	//// Front
	//m_cube2Indices.push_back(0);
	//m_cube2Indices.push_back(1);
	//m_cube2Indices.push_back(2);
	//m_cube2Indices.push_back(0);
	//m_cube2Indices.push_back(2);
	//m_cube2Indices.push_back(3);
	//// Back
	//m_cube2Indices.push_back(4);
	//m_cube2Indices.push_back(7);
	//m_cube2Indices.push_back(6);
	//m_cube2Indices.push_back(4);
	//m_cube2Indices.push_back(6);
	//m_cube2Indices.push_back(5);
	//// Right
	//m_cube2Indices.push_back(8);
	//m_cube2Indices.push_back(9);
	//m_cube2Indices.push_back(10);
	//m_cube2Indices.push_back(8);
	//m_cube2Indices.push_back(10);
	//m_cube2Indices.push_back(11);
	//// Left
	//m_cube2Indices.push_back(12);
	//m_cube2Indices.push_back(13);
	//m_cube2Indices.push_back(14);
	//m_cube2Indices.push_back(12);
	//m_cube2Indices.push_back(14);
	//m_cube2Indices.push_back(15);
	//// Top
	//m_cube2Indices.push_back(16);
	//m_cube2Indices.push_back(17);
	//m_cube2Indices.push_back(18);
	//m_cube2Indices.push_back(16);
	//m_cube2Indices.push_back(18);
	//m_cube2Indices.push_back(19);
	//// Bottom
	//m_cube2Indices.push_back(20);
	//m_cube2Indices.push_back(21);
	//m_cube2Indices.push_back(22);
	//m_cube2Indices.push_back(20);
	//m_cube2Indices.push_back(22);
	//m_cube2Indices.push_back(23);
}

void Assignment_3::createCubeMap(std::vector<std::string> filePaths)
{
	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_skyboxCubeMap);
	glTextureStorage2D(m_skyboxCubeMap, 1, GL_RGB8, 2048, 2048);
	for (size_t i = 0; i < filePaths.size(); ++i) {
		auto* orig_img = IMG_Load(filePaths[i].c_str());

		// NOTE: following image flip code copied from texture.cpp
		// Flip loaded image vertically
		// Might not be the most efficient implementation.. memcpy() would probably be faster with a separate row buffer
		//for (int y = 0; y < orig_img->h / 2; ++y)
		//{
		//	Uint32 *ptr1 = reinterpret_cast<Uint32 *>(static_cast<Uint8 *>(orig_img->pixels) + ((y)* orig_img->pitch));
		//	Uint32 *ptr2 = reinterpret_cast<Uint32 *>(static_cast<Uint8 *>(orig_img->pixels) + ((orig_img->h - 1 - y) * orig_img->pitch));

		//	// Swap elements of these rows. 
		//	for (int x = 0; x < orig_img->w; ++x)
		//		std::swap(*ptr1++, *ptr2++);
		//}
		glTextureSubImage3D(m_skyboxCubeMap, 0, 0, 0, i, orig_img->w, orig_img->h, 1, GL_RGB, GL_UNSIGNED_BYTE, orig_img->pixels);
		SDL_FreeSurface(orig_img);
	}
}

// NOTE: Mouse look around seems to be little laggy 
void Assignment_3::mouseMotion() {
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	if (x < 0) {
		//m_camera.rotYaw(-.05f);
		m_camera.setRotationYaw(-1.0f);
	}
	else if(x>0) {
		//m_camera.rotYaw(.05f);
		m_camera.setRotationYaw(1.0f);
	}

	if (y < 0) {
		//m_camera.rotPitch(.05f);
		m_camera.setRotationPitch(1.0f);
	}
	else if (y > 0) {
		//m_camera.rotPitch(-.05f);
		m_camera.setRotationPitch(-1.0f);
	}
}