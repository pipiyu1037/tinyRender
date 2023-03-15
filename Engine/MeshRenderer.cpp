#include "MeshRenderer.h"
#include "ShadowMap.h"
#include "RenderBase.h"

void MeshRenderer::Draw() {
	material->Set();
	model->Draw(material->GetShader());
}

void MeshRenderer::DrawShadowPass() {
	RenderBase::SetModelMatrix(ShadowMap::mainShadowMap->GetShadowShader(), *this);
	model->DrawNoTexture(ShadowMap::mainShadowMap->GetShadowShader());
}
