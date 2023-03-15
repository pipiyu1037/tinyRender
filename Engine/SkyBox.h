#pragma once
#include "Shader.h"

class SkyBox
{
public:
	SkyBox() {}
	void init();
	void Draw();

private:
	static float skyboxVertices[108];

	static Shader& GetShader() {
		static Shader shader("shaders/vertex_skybox.glsl", "shaders/frag_skybox.glsl");
		return shader;
	}
	unsigned int skyboxVAO;
	unsigned int cubemapTexture;
};

