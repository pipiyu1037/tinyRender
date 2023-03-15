#pragma once
#include "Component.h"
#include "IHaveShadowPass.h"
#include "Model.h"
#include "Material.h"
#include "MeshLoader.h"
#include "ROManager.h"

#include <memory>
#include <utility>

class Material;

class MeshRenderer :
	public Component,
	public IHaveShadowPass
{
public:
	MeshRenderer(GameObject& gameObject, std::string path) :
		Component(gameObject, "MeshRenderer"),
		model(MeshLoader::GetModel(path)),
		renderQueue(1000) {}

	template<class TMaterial, class ...Args>
	void AddMaterial(Args&&... args);

	template<class TMaterial>
	void AddMaterial();

	void Draw() override;
	void DrawShadowPass() override;
	int GetRenderQueue() override {
		return renderQueue;
	}

	void Update() override {}

	std::unique_ptr<Material> material;

private:
	std::shared_ptr<Model> model;
	int renderQueue;
};

template<class TMaterial, class ...Args>
void MeshRenderer::AddMaterial(Args && ...args) {
	material = std::make_unique<TMaterial>(*this, args);
}

template<class TMaterial>
inline void MeshRenderer::AddMaterial() {
	material = std::make_unique<TMaterial>(*this);
}
