#include "ShadowMap.h"
#include "RenderBase.h"
#include "DirectionalLight.h"
#include "Camera.h"

ShadowMap* ShadowMap::mainShadowMap = nullptr;

ShadowMap::~ShadowMap() {
	mainShadowMap = nullptr;
}

void ShadowMap::Init() {
	mainShadowMap = this;

	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::SetPassBegin() {
	GetShadowShader().use();

	glEnable(GL_DEPTH_TEST);

	if (auto camera = RenderBase::mainCamera.lock()) {
		glm::vec3 camPos = camera->Position;
		glm::vec3 lightDir;
		if (DirectionalLight::mainDirLight) {
			lightDir = DirectionalLight::mainDirLight->direction;
		}
		GLfloat near_plane = 1.0f, far_plane = 15.0f;
		glm::mat4 lightProjection = glm::ortho(
				-7.0f, 7.0f, 
				-7.0f, 7.0f, 
				near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt(
				camPos - lightDir * 5.0f, 
				camPos,
				glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;
		GetShadowShader().setMat4("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));
	}

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_FRONT);
}

void ShadowMap::SetPassEnd() {
	glCullFace(GL_BACK);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, RenderBase::SCR_WIDTH, RenderBase::SCR_HEIGHT);
}

Shader& ShadowMap::GetShadowShader() {
	static Shader shader("shaders/vertex_shadow.glsl", "shaders/frag_shadow.glsl");
	return shader;
}
