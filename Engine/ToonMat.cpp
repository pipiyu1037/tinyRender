#include "ToonMat.h"
#include "RenderBase.h"
#include "DirectionalLight.h"
#include "ShadowMap.h"

void ToonMat::Set()
{
	ToonMat::GetShader().use();

	RenderBase::SetMatrix(ToonMat::GetShader(), meshRenderer);

	if (DirectionalLight::mainDirLight) {
		ToonMat::GetShader().setVec3("dirlight0.direction",
			DirectionalLight::mainDirLight->direction.x,
			DirectionalLight::mainDirLight->direction.y,
			DirectionalLight::mainDirLight->direction.z);
		ToonMat::GetShader().setVec3("dirlight0.color",
			DirectionalLight::mainDirLight->color.x,
			DirectionalLight::mainDirLight->color.y,
			DirectionalLight::mainDirLight->color.z);
		ToonMat::GetShader().setFloat("dirlight0.intensity",
			DirectionalLight::mainDirLight->intensity);
	}

	if (ShadowMap::mainShadowMap) {
		glActiveTexture(GL_TEXTURE0 + 10);
		ToonMat::GetShader().setInt("shadowMap", 10);
		glBindTexture(GL_TEXTURE_2D, ShadowMap::mainShadowMap->depthMap);
		glActiveTexture(GL_TEXTURE0);
	}

	for (auto iter : properties) {
		ToonMat::GetShader().setFloat(iter.first, iter.second.value);
	}
	
}