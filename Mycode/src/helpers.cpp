#include "../include/helpers.h"

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
