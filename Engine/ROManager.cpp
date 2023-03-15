#include "ROManager.h"
#include "RenderBase.h"
#include "MessageOut.h"
#include "Engine.h"
#include "ShadowMap.h"
#include "Camera.h"
#include "SkyBox.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::multiset<RenderObject>
	ROManager::ROSet;
std::unordered_map<IHaveShadowPass*, std::weak_ptr<IHaveShadowPass> >
	ROManager::shadowCasters;

void ROManager::Render()
{
	for (auto it = ROSet.begin(); it != ROSet.end(); ++it) {
		if (it->expired) {
			it = ROSet.erase(it);
		}
	}
	int lastRenderQueue = -1;

	if (ShadowMap::mainShadowMap) {

		ShadowMap::mainShadowMap->SetPassBegin();

		for (auto it = shadowCasters.begin(); it != shadowCasters.end(); ++it) {
			auto casterPtr = it->second.lock();
			if (!casterPtr) {
				it = shadowCasters.erase(it);
			}
			else {
				casterPtr->DrawShadowPass();
			}
		}

		ShadowMap::mainShadowMap->SetPassEnd();
	}

	//MessageOut::Console << "ShadowCaster num: " << shadowCasters.size() << "\n";

	glClearColor(0.1914f, 0.3008f, 0.4727f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	RenderBase::skyBox->Draw();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (auto& renderObject : ROSet) {
		if (renderObject.renderQueue != lastRenderQueue) {
			glClear(GL_DEPTH_BUFFER_BIT);
			lastRenderQueue = renderObject.renderQueue;
			if (lastRenderQueue >= 3000) { // UI layer
				glDisable(GL_DEPTH_TEST);
			}
		}
		renderObject.Draw();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(RenderBase::window);
	glfwPollEvents();

	if (glfwWindowShouldClose(RenderBase::window)) {
		Engine::Exit();
	}
}

void ROManager::AddObject(std::weak_ptr<IRenderable> renderable, int renderQueue) {
	ROSet.emplace(renderable, renderQueue);
}

void ROManager::AddShadowCaster(std::shared_ptr<IHaveShadowPass> caster) {
	shadowCasters.emplace(caster.get(), caster);
}
