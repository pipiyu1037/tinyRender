#pragma once
#include "DirectionalLight.h"
#include "Camera.h"
#include "MyScript.h"

template<class TMaterial>
static void CreateModel(
	std::string name, 
	std::string path, 
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)) {
	auto newModel = GOManager::MakeGameObject(name);
	newModel->AddComponent<MeshRenderer>(path);
	newModel->transform.position = position;
	newModel->transform.scale = scale;
	auto MR = newModel->GetComponent<MeshRenderer>();
	MR->AddMaterial<TMaterial>();
}

static void GMScene0() {
	auto camera = GOManager::MakeGameObject("Camera");
	camera->AddComponent<Camera>(glm::vec3(0.0f, 1.3f, 2.0f));
	auto camCompo = camera->GetComponent<Camera>();
	RenderBase::SetMainCamera(camCompo);
	camera->AddComponent<CharacterController>();
	IMouseReceiver::SetCurrentReceiver(*camCompo);

	auto directionalLight = GOManager::MakeGameObject("DirectionalLight");
	directionalLight->AddComponent<DirectionalLight>();

	/*CreateModel<ToonMat>(
		"Keqing",
		"models/o/keqing.obj",
		glm::vec3(0.5f, 0.0f, 0.0f),
		glm::vec3(0.075f, 0.075f, -0.075f));*/
	auto newModel = GOManager::MakeGameObject("Keqing");
	newModel->AddComponent<MeshRenderer>("models/o/keqing.obj");
	newModel->transform.position = glm::vec3(0.5f, 0.0f, 0.0f);
	newModel->transform.scale = glm::vec3(0.075f, 0.075f, -0.075f);
	auto MR = newModel->GetComponent<MeshRenderer>();
	MR->AddMaterial<ToonMat>();

	newModel->AddComponent<MyScript>();


	CreateModel<PhongMat>(
		"Nanosuit",
		"models/nanosuit/nanosuit.obj",
		glm::vec3(-0.5f, 0.0f, 0.0f),
		glm::vec3(0.1f, 0.1f, 0.1f));

	CreateModel<PhongMat>(
		"StonePlane1",
		"models/plain/stonePlane.obj",
		glm::vec3(3.0f, 0.0f, 3.0f),
		glm::vec3(3.0f, 1.0f, 3.0f));
	CreateModel<PhongMat>(
		"StonePlane2",
		"models/plain/stonePlane.obj",
		glm::vec3(-3.0f, 0.0f, 3.0f),
		glm::vec3(3.0f, 1.0f, 3.0f));
	CreateModel<PhongMat>(
		"StonePlane3",
		"models/plain/stonePlane.obj",
		glm::vec3(3.0f, 0.0f, -3.0f),
		glm::vec3(3.0f, 1.0f, 3.0f));
	CreateModel<PhongMat>(
		"StonePlane4",
		"models/plain/stonePlane.obj",
		glm::vec3(-3.0f, 0.0f, -3.0f),
		glm::vec3(3.0f, 1.0f, 3.0f));

	
}