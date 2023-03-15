#include "GameObject.h"

int GameObject::idAllocator = 0;

void GameObject::Update()
{
	for (auto compoPtr : components) {
		// MessageOut::Console << name << ": " << compoPtr->name << "\n";
		compoPtr->Update();
	}
}

bool GameObject::CheckExisting(std::string name)
{
	if (compoNameSet.count(name)) {
		MessageOut::Console << "Error: Adding a existed component \"" <<
			name << "\" to GameObject #" << id << ": \"" << name << "\".\n";
		return true;
	}
	else {
		compoNameSet.insert(name);
		return false;
	}
}
