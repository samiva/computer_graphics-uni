#include "../include/MonkeyScene.h"
#include "../../cg-sources/objparser.h"
#include "../include/helpers.h"
#include <iostream>

void MonkeyScene::loadMonkey()
{
	m_obj.load("../../models/monkey.obj");
	std::cout << "------------MONKEY SCENE-----------------" << std::endl;
	auto it = m_obj.objVertexSet.begin();
	auto vb = it->second.vertexBuffers[0];
	std::cout << "Vertices" << std::endl;
	for (const auto elem : vb.pos) {
		std::cout << "pos: (" << elem.x << ", " << elem.y << ", " << elem.z << ")" << std::endl;
	}
	if (vb.hasNormal()) {
		for (const auto elem : vb.normal) {
			std::cout << "normal: (" << elem.x << ", " << elem.y << ", " << elem.z << ")" << std::endl;
		}
	}
	std::cout << "indices" << std::endl;
	for (const auto elem : vb.indices) {
		std::cout << "indx: "<<elem << std::endl;
	}

	std::cout << "Vertices, normals and indices" << std::endl;
	for (const auto i : vb.indices) {
		std::cout << "Index: " << i << std::endl;
		std::cout << "Position: (" << vb.pos[i].x << ", " << vb.pos[i].y<<", " << vb.pos[i].z << ") " << std::endl;
		std::cout << "Normal: (" << vb.normal[i].x << ", " << vb.normal[i].y<<", " << vb.normal[i].z << ") " << std::endl;

	}
	for (int i = 0; i < vb.pos.size(); ++i) {
		m_cubeVertices.push_back(Vertex(vb.pos[i].x, vb.pos[i].y, vb.pos[i].z, vb.normal[i].x, vb.normal[i].y, vb.normal[i].z));
	}
	//m_vertices = vb.pos;
	m_cubeIndices = vb.indices;
	
}

MonkeyScene::MonkeyScene()
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

MonkeyScene::~MonkeyScene()
{
}

bool MonkeyScene::init()
{
	
	// Load shader program used in this example
	auto shaders = getShaderPaths("Lightning");
	if (!shaderProgram.load(shaders[0], shaders[1]))
		return false;


	// Use shader program to render everything
	glUseProgram(shaderProgram.getShaderProgram());

	//Initialize clear color for glClear()
	glClearColor(0.2f, 0.3f, 0.1f, 1.f);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);

	// Enable blending (slower but necessary for partially transparent objects)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Allocate and assign a Vertex Array Object to our handle
	glGenVertexArrays(1, &vao);

	// Bind our Vertex Array Object as the currently used object
	// VAO will hold the state of our IBO and VBO below. Also any
	// settings selected for these buffer objects will be part of the VAO state as well.
	glBindVertexArray(vao);

	// Create Index Buffer Object
	glGenBuffers(1, &ebo);

	// Bind our Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Store our index values in Index Buffer Object
	// GL_STATIC_DRAW means that we don't expect this buffer to change (It's a hint that it can be stored on GPU)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndices.size() * sizeof(unsigned int), &m_cubeIndices[0], GL_STATIC_DRAW);

	// Allocate and assign One Vertex Buffer Object to our handle
	glGenBuffers(1, &vbo);

	// Bind our VBO as being the active buffer and storing vertex attributes (coordinates + colors)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Copy the vertex data from tetrahedron to our buffer
	// 12 * sizeof(GLfloat) is the size of the tetrahedrom array, since it contains 12 Vertex values
	// GL_STATIC_DRAW means that we don't expect this buffer to change (It's a hint that it can be stored on GPU)
	glBufferData(GL_ARRAY_BUFFER, m_cubeVertices.size() * sizeof(Vertex), &m_cubeVertices[0], GL_STATIC_DRAW);

	// Note: The following attribute indexes must match what is defined in shader (in shaderprogram.cpp) for glBindAttribLocation() calls!

	// Specify that our coordinate data is going into attribute index 0 (shaderProgram.getPositionAttribLocation()), and contains three doubles per vertex
	// Note stride = sizeof ( struct Vertex ) and pointer = ( const GLvoid* ) 0
	glVertexAttribPointer(shaderProgram.getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, position)));

	// Enable attribute index 0 as being used
	glEnableVertexAttribArray(shaderProgram.getPositionAttribLocation());

	// Normal vertex attribute
	glVertexAttribPointer(shaderProgram.getNormalAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));

	glEnableVertexAttribArray(shaderProgram.getNormalAttribLocation());

	// Our generated VAO is now ready and enabled for use
	// We could disable by calling glBindVertexArray(0) if we want to work with multiple objects and not use created VAO at the moment.

	// Set up our view matrix that determines camera position in the scene
	// glm::lookAt replaces old GLU library functionality for creating a projection matrix
	viewMat = glm::lookAt(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	return true;
}

void MonkeyScene::resize(GLsizei width, GLsizei height)
{
	// Update OpenGL viewport to match window system's window size
	glViewport(0, 0, width, height);

	// Set up projection matrix and model matrix etc.
	float fovy = 45.0f;
	projectionMat = glm::perspective(fovy, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}

void MonkeyScene::update(float timestep)
{
	m_yaw += glm::two_pi<float>() * 0.1f * timestep;
	m_posY = glm::sin(m_counter);
	m_posZ = glm::cos(m_counter);
	m_counter += .001f;
	
}

void MonkeyScene::render()
{
	// Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate model transformation
	auto T = glm::translate(glm::mat4(), glm::vec3(0, m_posY, m_posZ));
	auto R = glm::rotate(glm::mat4(), m_yaw, glm::vec3(0.0, 1.0, 0.0)); // Rotate object around y-axis
	auto modelMat = T * R;

	// Select correct shader program for this object (we never selected anything else to replace that state after init())
	glUseProgram(shaderProgram.getShaderProgram());

	glm::vec4 viewPos(0.0f, 1.0f, 5.0f, 1.0f);
	auto modelviewMat = viewMat * modelMat;
	glm::vec4 lightPos(2.0f, 2.0f, 3.0f, 1.0f);
	auto lightInView = viewMat * lightPos;


	// light properties
	glm::vec4 lAmbient(0.2, 0.2, 0.2, 1.0);
	glm::vec4 lDiffuse(1.0, 1.0, 1.0, 1.0);
	glm::vec4 lSpecular(1.0);

	// Material propertries
	glm::vec4 mAmbient(1.0, 0.0, 1.0, 1.0);
	glm::vec4 mDiffuse(1.0, 0.8, 0.0, 1.0);
	glm::vec4 mSpecular(1.0, 0.8, 0.0, 1.0);
	glm::vec4 mEmission(0.0, 0.3, 0.3, 1.0);
	float mShininess = 10;

	glm::vec4 ambientProduct = lAmbient * mAmbient;
	glm::vec4 diffuseProduct = lDiffuse * mDiffuse;
	glm::vec4 specularProduct = lSpecular * mSpecular;

	glm::vec3 color(.5,0,0);

	// set uniforms
	glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "ambientProduct"), 1, glm::value_ptr(ambientProduct));
	glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "diffuseProduct"), 1, glm::value_ptr(diffuseProduct));
	glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "specularProduct"), 1, glm::value_ptr(specularProduct));
	glUniform1fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "mShininess"), 1, &mShininess);
	glUniform3fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "color"), 1, glm::value_ptr(color));

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelviewMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getShaderProgram(),"projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));
	
	
	glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "lightPos"), 1, glm::value_ptr(lightInView));

	//glUniform4fv(glGetUniformLocation(shaderProgram.getShaderProgram(), "viewpos"), 1, glm::value_ptr(viewPos));

	// Get uniform lighcolor from shader program
	GLint lightColorLoc = glGetUniformLocation(shaderProgram.getShaderProgram(), "lightcolor");

	glm::vec3 ambLightColor(1.0f);
	// Set light color for shader
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(ambLightColor));
	
	// For drawing the cube it needs to be bound using (we never bound anything else to replace that state after init())
	glBindVertexArray(vao);

	// Count is the number of elements in the array that will form triangles. It is not the number of triangles defined by the array.
	// When VBOs are in use and GL_ELEMENT_ARRAY_BUFFER is bound, the last parameter (pointer to data) is interpreted as an offset within IBO instead of
	// actual program memory address.
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_cubeIndices.size()), GL_UNSIGNED_INT, 0);
}

bool MonkeyScene::handleEvent(const SDL_Event & e)
{
	return true;
}
