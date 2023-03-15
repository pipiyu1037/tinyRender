#pragma once
#include "Material.h"
class ToonMat : public Material
{
public:
	ToonMat(MeshRenderer& meshRenderer) :
		Material(meshRenderer) {
		properties.emplace("glossiness", Property(4.0f, 0.5f, 64.0f));
	}

public:
	void Set() override;

	Shader& GetShader() override {
		static Shader shader("shaders/vertex.glsl", "shaders/frag_toon.glsl");
		return shader;
	}
};

