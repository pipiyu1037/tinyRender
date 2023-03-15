#pragma once
#include "Component.h"
#include "imgui.h"
#include "IRenderable.h"

class ImGuiWidget :
    public Component,
    public IRenderable
{
public:
    ImGuiWidget(GameObject& gameObject) :
        Component(gameObject, "ImGuiWidget"),
        renderQueue(3000) {}

    int GetRenderQueue() override {
        return renderQueue;
    }

    void Update() override {}

private:
    int renderQueue;
};

