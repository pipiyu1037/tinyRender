#include "RenderBase.h"
#include "MessageOut.h"
#include "Input.h"
#include "ShadowMap.h"
#include "Camera.h"
#include "ShadowMap.h"
#include "MeshRenderer.h"
#include "SkyBox.h"
#include "GameObject.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Enable RTX2060
extern "C" __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
// Enable AMD
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int RenderBase::SCR_WIDTH = 800;
int RenderBase::SCR_HEIGHT = 600;

GLFWwindow* RenderBase::window = nullptr;
std::weak_ptr<Camera> RenderBase::mainCamera = std::weak_ptr<Camera>();
std::shared_ptr<ShadowMap> RenderBase::shadowMap = std::shared_ptr<ShadowMap>();
std::shared_ptr<SkyBox> RenderBase::skyBox = std::shared_ptr<SkyBox>();

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	RenderBase::SCR_WIDTH = width;
	RenderBase::SCR_HEIGHT = height;
}

void RenderBase::Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);

	SCR_WIDTH = mode->width / 1.5;
	SCR_HEIGHT = mode->height / 1.5;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Little Renderer", NULL, NULL);
	if (window == NULL)
	{
		MessageOut::Console << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MessageOut::Console << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, Input::scroll_callback);
	glfwSetMouseButtonCallback(window, Input::mouse_button_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	shadowMap = std::make_shared<ShadowMap>();
	shadowMap->Init();

	skyBox = std::make_shared<SkyBox>();
	skyBox->init();

	stbi_set_flip_vertically_on_load(true);
}

void RenderBase::SetMatrix(const Shader& shader, const MeshRenderer& meshRenderer) {
	auto camera = mainCamera.lock();
	if (!camera) {
		MessageOut::Console << "Main camera is missing!\n";
		return;
	}

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	shader.setMat4("view", glm::value_ptr(view));
	shader.setMat4("projection", glm::value_ptr(projection));
	shader.setVec3("viewPos", camera->Position.x, camera->Position.y, camera->Position.z);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, meshRenderer.gameObject.transform.position);
	model = glm::scale(model, meshRenderer.gameObject.transform.scale);
	shader.setMat4("model", glm::value_ptr(model));

	model = glm::inverse(model);
	model = glm::transpose(model);
	shader.setMat4("normalInv", glm::value_ptr(model));

	if(ShadowMap::mainShadowMap)
		shader.setMat4("lightSpaceMatrix", glm::value_ptr(ShadowMap::mainShadowMap->lightSpaceMatrix));
}

void RenderBase::SetModelMatrix(const Shader& shader, const MeshRenderer& meshRenderer) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, meshRenderer.gameObject.transform.position);
	model = glm::scale(model, meshRenderer.gameObject.transform.scale);
	shader.setMat4("model", glm::value_ptr(model));
}