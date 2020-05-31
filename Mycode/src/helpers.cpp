#include "../include/helpers.h"
#include "cg-sources/objparser.h"
#include <iostream>

std::vector<std::string> getShaderPaths(const std::string shaderName)
{
	std::vector<std::string> shaderPaths = {
	"../../Shaders/" + shaderName +".vs",
	"../../Shaders/" + shaderName + ".fs"
	};
	return shaderPaths;
}

std::vector<std::string> getSkyboxImages()
{
	const std::string folder = "../../res/space/lightblue/";
	std::vector<std::string> imagepaths = {
		folder + "right.png", folder +"left.png",
		folder + "top.png", folder + "bot.png", 
		folder + "back.png", folder+"front.png"};
	return imagepaths;
}

void loadModel(const std::string& name, std::vector<Vertex>& verts, std::vector<unsigned int>& inds)
{
	std::string folder = "../../models/";
	ObjParser obj;
	obj.load(folder + name);
	std::cout << "------------MONKEY SCENE-----------------" << std::endl;
	auto it = obj.objVertexSet.begin();
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
		std::cout << "indx: " << elem << std::endl;
	}

	std::cout << "Vertices, normals and indices" << std::endl;
	for (const auto i : vb.indices) {
		std::cout << "Index: " << i << std::endl;
		std::cout << "Position: (" << vb.pos[i].x << ", " << vb.pos[i].y << ", " << vb.pos[i].z << ") " << std::endl;
		std::cout << "Normal: (" << vb.normal[i].x << ", " << vb.normal[i].y << ", " << vb.normal[i].z << ") " << std::endl;

	}
	for (int i = 0; i < vb.pos.size(); ++i) {
		verts.push_back(Vertex(static_cast<glm::vec3>(vb.pos[i]), vb.normal[i]));
	}
	//m_vertices = vb.pos;
	inds = vb.indices;
}
