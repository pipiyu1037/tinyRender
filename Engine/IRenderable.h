#pragma once
class IRenderable // interface
{
public:
	virtual void Draw() = 0;
	virtual int GetRenderQueue() = 0;
};

