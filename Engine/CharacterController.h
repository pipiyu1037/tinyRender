#pragma once
#include "Component.h"
class CharacterController : public Component
{
public:
	CharacterController(GameObject& gameObject) :
		Component(gameObject, "CharacterController") {
		speed = 2.0f;
		jumpForce = 4.0f;
	}

	void Update() override;

private:
	float speed;
	float jumpForce;
};

