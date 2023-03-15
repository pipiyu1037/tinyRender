#pragma once
#include "IRenderable.h"

#include <memory>

class RenderObject
{
public:
	RenderObject(
		std::weak_ptr<IRenderable> renderable,
		int renderQueue) :
		renderable(renderable),
		renderQueue(renderQueue),
		expired(false) {}

public:
	int renderQueue;
	mutable bool expired;

	bool operator<(const RenderObject& rhs) const {
		return renderQueue < rhs.renderQueue;
	}

	void Draw() const;

private:
	std::weak_ptr<IRenderable> renderable;
};

