#pragma once
#include "Component.h"
#include "Time.h"
#include "Input.h"

#include <cmath>

class MyScript : public Component{
public:
	MyScript(GameObject& gameObject) :
		Component(gameObject, "MyScript") {}

public:
	void Update() override {
		if (Input::GetKey(Input::Key_K)) {
			gameObject.transform.position.x = sin(Time::time) * 2.0f;
			gameObject.transform.position.z = cos(Time::time) * 2.0f;
		}
	}
};

