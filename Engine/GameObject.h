#pragma once
#include "MessageOut.h"
#include "Transform.h"
#include "IRenderable.h"
#include "ROManager.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <type_traits>
#include "Component.h"


class GameObject 
{
public:
	GameObject(const std::string& name) :
		name(name) {
		id = ++idAllocator;
	}

public:
	int id;
	std::string name;
	Transform transform;

	template<class TComponent, class... Args>
	bool AddComponent(Args&&... args);

	template<class TComponent, class... Args>
	bool AddComponent();

	template<class TComponent>
	std::shared_ptr<TComponent> GetComponent();

	void Update();

private:
	bool CheckExisting(std::string name);

	template<class TComponent>
	void AcceptComponent(std::shared_ptr<Component> &newCompo);

	static int idAllocator;

	std::vector<std::shared_ptr<Component>> components;
	std::unordered_set<std::string> compoNameSet;
};

template<class TComponent>
static void AddShadowCaster(
	std::shared_ptr<Component> &caster,
	std::true_type) {
	auto IHCompo = std::dynamic_pointer_cast<IHaveShadowPass>(caster);
	ROManager::AddShadowCaster(IHCompo);
	return;
}

template<class TComponent>
static void AddShadowCaster(
	std::shared_ptr<Component> &caster,
	std::false_type) {
	return;
}

template<class TComponent>
static void AddToROManager(
	std::shared_ptr<Component> &newRenderable,
	std::true_type) {
	auto IRCompo = std::dynamic_pointer_cast<IRenderable>(newRenderable);
	ROManager::AddObject(IRCompo, IRCompo->GetRenderQueue());

	AddShadowCaster<TComponent>(
		newRenderable,
		std::is_base_of<IHaveShadowPass, std::decay_t<TComponent> >());
	return;
}

template<class TComponent>
static void AddToROManager(
	std::shared_ptr<Component> &newRenderable,
	std::false_type) {
	return;
}

template<class TComponent>
void GameObject::AcceptComponent(std::shared_ptr<Component> &newCompo) {
	components.push_back(newCompo);

	AddToROManager<TComponent>(
		newCompo,
		std::is_base_of<IRenderable, std::decay_t<TComponent> >());
}

template<class TComponent, class ...Args>
bool GameObject::AddComponent(Args && ...args) {
	std::shared_ptr<Component> newCompo =
		std::make_shared<TComponent>(*this, std::forward<Args>(args)...);
	if (CheckExisting(newCompo->name)) {
		return false;
	}
	else {
		AcceptComponent<TComponent>(newCompo);
		return true;
	}
}

template<class TComponent, class ...Args>
bool GameObject::AddComponent() {
	std::shared_ptr<Component> newCompo =
		std::make_shared<TComponent>(*this);
	if (CheckExisting(newCompo->name)) {
		return false;
	}
	else {
		AcceptComponent<TComponent>(newCompo);
		return true;
	}
}

template<class TComponent>
std::shared_ptr<TComponent> GameObject::GetComponent()
{
	std::shared_ptr<TComponent> result;
	for (auto compoPtr : components) {
		result = std::dynamic_pointer_cast<TComponent>(compoPtr);
		if (result.get()) {
			break;
		}
	}
	return result;
}