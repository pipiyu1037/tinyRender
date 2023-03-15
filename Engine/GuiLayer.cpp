#include "GuiLayer.h"
#include "GOManager.h"
#include "MeshRenderer.h"
#include "Input.h"
#include "Camera.h"
#include "RenderBase.h"
#include "Time.h"
#include "ToonMat.h"
#include <string>
#include "Engine.h"
#include "DirectionalLight.h"

void addObj() {
	auto nanosuit6 = GOManager::MakeGameObject("Nanosuit6");
	nanosuit6->AddComponent<MeshRenderer>("models/nanosuit/nanosuit.obj");
	nanosuit6->transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
	nanosuit6->transform.scale = glm::vec3(0.1f, 0.1f, 0.1f);
	auto MR6 = nanosuit6->GetComponent<MeshRenderer>();
	MR6->AddMaterial<ToonMat>();
}

void showPropertyController() {
	auto MeshRenders = GOManager::GetAllComponents<MeshRenderer>();
	for (auto MR : MeshRenders) {
		auto properties = MR->material->GetProperties();
		std::string id = std::to_string(MR->gameObject.id);
		std::string name = MR->gameObject.name;
		if (ImGui::CollapsingHeader((name + " id:" + id).c_str())) {
			for (auto property : properties) {
				ImGui::SetNextItemWidth(300);
				ImGui::SliderFloat((property.first + id).c_str(), &(property.second.value),
					property.second.minVal, property.second.maxVal);
				MR->material->SetProperty(property.first, property.second.value);
			}
			int itemWidth = RenderBase::SCR_WIDTH / 6;
			ImGui::Separator();
			ImGui::Text("position");
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-position-X").c_str(), &(MR->gameObject.transform.position.x), -10.f, 10.f);
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-position-Y").c_str(), &(MR->gameObject.transform.position.y), -10.f, 10.f);
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-position-Z").c_str(), &(MR->gameObject.transform.position.z), -10.f, 10.f);
			ImGui::Separator();
			ImGui::Text("Scale");
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-scale-X").c_str(), &(MR->gameObject.transform.scale.x), 0.f, 0.3f);
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-scale-Y").c_str(), &(MR->gameObject.transform.scale.y), 0.f, 0.3f);
			ImGui::SetNextItemWidth(itemWidth);
			ImGui::SliderFloat((name + id + "-scale-Z").c_str(), &(MR->gameObject.transform.scale.z), 0.f, 0.3f);
		}
	}
}

void showLightControllor() {
	ImGui::Separator();
	DirectionalLight* DirLight = DirectionalLight::mainDirLight;
	static float nutationAngle = 45.f;
	static float precessionAngle = 0.f;
	static float color[3] = { 1.f,1.f,1.f };
	if (DirLight) {
		if (ImGui::CollapsingHeader("Light")) {
			ImGui::Text("Direction");
			ImGui::SliderFloat("NutationAngle", &nutationAngle, 0.f, 90.f);
			ImGui::SliderFloat("PrecessionAngle", &precessionAngle, 0.f, 360.f);
			DirectionalLight::mainDirLight->SetNutationAngle(nutationAngle);
			DirectionalLight::mainDirLight->SetPrecessionAngle(precessionAngle);
			ImGui::Separator();
			ImGui::Text("Color");
			ImGui::ColorEdit3("LightColor", color);
			DirectionalLight::mainDirLight->SetColor(color[0], color[1], color[2]);
		}
	}
}

void showExit() {
	if (ImGui::BeginChild("0")) {
		if (ImGui::Button("Exit", ImVec2(100, 20))) {
			Engine::Exit();
		}
	}
	ImGui::EndChild();
}
void GuiLayer::Draw() {
	/*static bool show_demo_window = true;
	static bool show_another_window = false;*/

	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static float x = 0.0f,y = 0.0f,z = 0.0f;
	static float glossiness = 0.0f;
	static bool displayGui = false;
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);*/
	
	if (Input::GetKeyDown(Input::Key_Escape)) {
		displayGui = !displayGui;
		auto camera = RenderBase::mainCamera.lock();
		if (displayGui) {
			camera->DisableReceive();
			Time::timeScale = 0.f;
		}
		else {
			camera->EnableReceive();
			Time::timeScale = 1.f;
		}
	}
	if (displayGui) {
		if (ImGui::Begin("GuiLayer")) {
			ImGui::SetWindowSize(ImVec2(RenderBase::SCR_WIDTH / 3, 800), ImGuiCond_Always);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			/*if (ImGui::Button("add model")) {
				addObj();
			}*/
			showPropertyController();
			showLightControllor();
			showExit();
		}

		ImGui::End();
	}
}