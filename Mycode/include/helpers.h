#ifndef __HELPERS_H__
#define __HELPERS_H__
#include <string>
#include <vector>
#include "vertex.h"

std::vector<std::string> getShaderPaths(const std::string shaderName);
std::vector<std::string> getSkyboxImages();
void loadModel(const std::string& name, std::vector<Vertex>& verts, std::vector<unsigned int>& inds);
#endif // !__HELPERS_H__