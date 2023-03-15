#include "RenderObject.h"

void RenderObject::Draw() const {
	if (auto ptr = renderable.lock()) {
		ptr->Draw();
	}
	else {
		expired = true;
	}
}
