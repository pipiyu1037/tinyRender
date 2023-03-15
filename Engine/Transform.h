#pragma once

#include <glm/glm.hpp>

class Transform
{
public:
	Transform() : 
		position(0.0f, 0.0f, 0.0f),
		scale(1.0f, 1.0f, 1.0f) {}

public:
	glm::vec3 position;
	glm::vec3 scale;
};

