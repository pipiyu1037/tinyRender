#pragma once
#include "Component.h"
class GameManager : public Component
{
public:
	GameManager(GameObject& gameObject) :
		Component(gameObject, "GameManager"),
		firstRun(true) {}

	void Update() override;

private:
	bool firstRun;
};

