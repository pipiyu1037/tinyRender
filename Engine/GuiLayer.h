#pragma once
#include "ImGuiWidget.h"

class GuiLayer : public ImGuiWidget
{
public:
	GuiLayer(GameObject& gameObject) :
		ImGuiWidget(gameObject) {}

	void Draw() override;
};

