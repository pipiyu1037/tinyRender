#pragma once
#include "ImGuiWidget.h"
class GuiSample : public ImGuiWidget
{
public:
	GuiSample(GameObject& gameObject) :
		ImGuiWidget(gameObject) {}

	void Draw() override;
};

/*
	README:
	This is a sample of a gui widget.

	Please copy and paste the constructor,
	and override the Draw() method.

	To activate your widget, add these code in
	the GameManager::Update():
	auto guiWindow = GOManager::MakeGameObject("GuiWindow");
	guiWindow->AddComponent<GuiSample>();
*/