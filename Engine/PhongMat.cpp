#include "PhongMat.h"
#include "RenderBase.h"
#include "DirectionalLight.h"
#include "ShadowMap.h"

void PhongMat::Set()
{
	PhongMat::GetShader().use();

	RenderBase::SetMatrix(PhongMat::GetShader(), meshRenderer);

	if (DirectionalLight::mainDirLight) {
		PhongMat::GetShader().setVec3("dirlight0.direction",
			DirectionalLight::mainDirLight->direction.x,
			DirectionalLight::mainDirLight->direction.y,
			DirectionalLight::mainDirLight->direction.z);
		PhongMat::GetShader().setVec3("dirlight0.color",
			DirectionalLight::mainDirLight->color.x,
			DirectionalLight::mainDirLight->color.y,
			DirectionalLight::mainDirLight->color.z);
		PhongMat::GetShader().setFloat("dirlight0.intensity",
			DirectionalLight::mainDirLight->intensity);
	}

	if (ShadowMap::mainShadowMap) {
		glActiveTexture(GL_TEXTURE0 + 10);
		PhongMat::GetShader().setInt("shadowMap", 10);
		glBindTexture(GL_TEXTURE_2D, ShadowMap::mainShadowMap->depthMap);
		glActiveTexture(GL_TEXTURE0);
	}

	for (auto iter : properties) {
		PhongMat::GetShader().setFloat(iter.first, iter.second.value);
	}
}
