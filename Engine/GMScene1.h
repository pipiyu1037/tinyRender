#pragma once
#include "GuiLayer.h"
static void GMScene1() {
	auto guiWindow = GOManager::MakeGameObject("GuiWindow");
	guiWindow->AddComponent<GuiLayer>();
}