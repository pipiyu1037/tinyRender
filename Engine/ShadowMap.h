#pragma once
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class ShadowMap {
public:
	ShadowMap() {}
	~ShadowMap();

public:
	void Init();
	void SetPassBegin();
	void SetPassEnd();
	Shader& GetShadowShader();
	glm::mat4 lightSpaceMatrix;

	static ShadowMap* mainShadowMap;

	GLuint depthMap;

private:
	GLuint depthMapFBO;
	const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
};

