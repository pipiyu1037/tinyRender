#pragma once
#include "IRenderable.h"
class IHaveShadowPass : public IRenderable {
public:
	virtual void DrawShadowPass() = 0;
};

