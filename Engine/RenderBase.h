#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

class Camera;
class ShadowMap;
class MeshRenderer;
class SkyBox;

class RenderBase // static class
{
private:
	RenderBase();

public:
	static void Init();
	static void SetMatrix(const Shader& shader, const MeshRenderer& meshRenderer);
	static void SetModelMatrix(const Shader& shader, const MeshRenderer& meshRenderer);
	static void SetMainCamera(std::shared_ptr<Camera> camera) {
		mainCamera = camera;
	}

	static GLFWwindow* window;
	static std::weak_ptr<Camera> mainCamera;
	static std::shared_ptr<ShadowMap> shadowMap;
	static std::shared_ptr<SkyBox> skyBox;

	static int SCR_WIDTH;
	static int SCR_HEIGHT;
};

