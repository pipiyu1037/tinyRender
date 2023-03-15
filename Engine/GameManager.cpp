#include "GameManager.h"
#include "MessageOut.h"
#include "Input.h"
#include "Engine.h"
#include "GOManager.h"
#include "PhongMat.h"
#include "ToonMat.h"
#include "CharacterController.h"
#include "GuiSample.h"

#include "GMScene0.h"
#include "GMScene1.h"
#include "GMScene2.h"

#include <glm/glm.hpp>

void GameManager::Update() {

	if (!firstRun)
		return;
	MessageOut::Console << "GameManager!" << std::endl;

	GMScene0();
	GMScene1();
	GMScene2();

	firstRun = false;
	
}
