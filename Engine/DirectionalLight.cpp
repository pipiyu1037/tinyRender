#include "DirectionalLight.h"
#include "Time.h"

#include <cmath>

DirectionalLight* DirectionalLight::mainDirLight = nullptr;

void DirectionalLight::Update() {
	static float pi = acos(-1);

	float nuta = nutationAngle / 180.0f * pi;
	float prec = precessionAngle / 180.0f * pi;

	direction.y = -sin(nuta);
	float h = cos(nuta);

	direction.x = h * cos(prec);
	direction.z = h * sin(prec);
}
