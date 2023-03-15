#pragma once

#include <unordered_map>
#include <string>

class ImageLoader { // static class
private:
	ImageLoader();

public:
	static unsigned int GetTexture(std::string path);

	static void Load();

private:
	static std::unordered_map<std::string, unsigned int> textureSet;
};

