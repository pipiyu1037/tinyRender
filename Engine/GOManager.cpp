#include "GOManager.h"

std::unordered_map<int, std::shared_ptr<GameObject>>
	GOManager::GOSet;
std::queue<std::shared_ptr<GameObject>>
	GOManager::insertQueue;

std::shared_ptr<GameObject> GOManager::MakeGameObject(const std::string& name)
{
	auto newGO = std::make_shared<GameObject>(name);
	insertQueue.push(newGO);
	return newGO;
}

void GOManager::Update()
{
	while (!insertQueue.empty()) {
		auto& newGO = insertQueue.front();
		GOSet.insert_or_assign(newGO->id, newGO);
		insertQueue.pop();
	}
	for (auto gameObjectPtr : GOSet) {
		gameObjectPtr.second->Update();
	}
}