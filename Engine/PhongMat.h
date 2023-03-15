#pragma once
#include "Material.h"
#include "Shader.h"

class PhongMat : public Material
{
public:
	PhongMat(MeshRenderer& meshRenderer) :
		Material(meshRenderer) {
		properties.emplace("glossiness", Property(16.0f, 0.5f, 64.0f));
	}

public:

	void Set() override;

	Shader& GetShader() override {
		static Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		return shader;
	}
};

