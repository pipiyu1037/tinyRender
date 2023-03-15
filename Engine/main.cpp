#include "Engine.h"
#include "Component.h"
#include "GOManager.h"
#include "MessageOut.h"
#include "GameManager.h"
#include "Input.h"

int main() {
	auto go1 = GOManager::MakeGameObject("GameManager");
	go1->AddComponent<GameManager>();

	Engine::Start();

	return 0;
}
