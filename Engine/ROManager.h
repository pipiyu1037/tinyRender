#pragma once
#include "RenderObject.h"
#include "IRenderable.h"
#include "IHaveShadowPass.h"

#include <set>
#include <unordered_map>
#include <memory>

class ROManager // static class
{
private:
	ROManager();

public:
	static void Render();
	static void AddObject(std::weak_ptr<IRenderable> renderable, int renderQueue);
	static void AddShadowCaster(std::shared_ptr<IHaveShadowPass> caster);

private:
	static std::multiset<RenderObject> ROSet;
	static std::unordered_map<IHaveShadowPass*, std::weak_ptr<IHaveShadowPass> > shadowCasters;
};