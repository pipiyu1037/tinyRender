#pragma once

#include <memory>
#include <string>

class GameObject;

class Component
{
public:
	Component(GameObject &gameObject,
		const std::string& name) :
		gameObject(gameObject) , name(name) {}
	virtual ~Component() = default;

	virtual void Update() = 0;

public:
	GameObject &gameObject;
	std::string name;
};
