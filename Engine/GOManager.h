#pragma once
#include "GameObject.h"

#include <string>
#include <unordered_map>
#include <memory>
#include <queue>
#include <vector>

class GOManager // static class
{
private:
	GOManager();

public:
	static std::shared_ptr<GameObject> MakeGameObject(const std::string& name);
	static void Update();

	template<class TComponent>
	static std::vector<TComponent*> GetAllComponents();

private:
	static std::unordered_map<int, std::shared_ptr<GameObject>> GOSet;
	static std::queue<std::shared_ptr<GameObject>> insertQueue;
};

template<class TComponent>
std::vector<TComponent*> GOManager::GetAllComponents() {
	std::vector<TComponent*> result = std::vector<TComponent*>();
	for (auto GO : GOSet) {
		auto TC_ptr = GO.second->GetComponent<TComponent>();
		if (TC_ptr.get()) {
			result.push_back(TC_ptr.get());
		}
	}
	return result;
}
