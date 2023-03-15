#pragma once
#include "Component.h"

#include <glm/glm.hpp>

class DirectionalLight : public Component {
public:
	DirectionalLight(GameObject& gameobject) :
		Component(gameObject, "DirectionalLight") {
		mainDirLight = this;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		intensity = 1.0f;
		nutationAngle = 45.0f;
		precessionAngle = 0.0f;
	}

	~DirectionalLight() {
		if (mainDirLight == this) {
			mainDirLight = nullptr;
		}
	}

public:
	static DirectionalLight* mainDirLight;

	void SetColor(float r, float g, float b) {
		color = glm::vec3(r, g, b);
	}

	// 0 ~ 90
	void SetNutationAngle(float angle) {
		nutationAngle = angle;
	}

	// 0 ~ 360
	void SetPrecessionAngle(float angle) {
		precessionAngle = angle;
	}

	void Update() override;

	glm::vec3 direction;
	glm::vec3 color;
	float intensity;

private:
	float nutationAngle;
	float precessionAngle;
};

