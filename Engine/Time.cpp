#include "Time.h"

float Time::deltaTime = 0;
float Time::time = 0;

double Time::dbDeltaTime = 0;
double Time::dbTime = 0;

float Time::unscaledDeltaTime = 0;
float Time::unscaledTime = 0;

float Time::timeScale = 1.0f;

std::chrono::steady_clock::time_point Time::beginTime;
std::chrono::steady_clock::time_point Time::lastTime;

void Time::Init() {
	using namespace std::chrono;

	beginTime = steady_clock::now();
	lastTime = beginTime;
}

void Time::Update() {
	using namespace std::chrono;

	auto nowTime = steady_clock::now();
	auto duration = duration_cast<nanoseconds>(nowTime - lastTime);
	dbDeltaTime = duration.count() / 1000000000.0;
	unscaledDeltaTime = static_cast<float>(dbDeltaTime);

	duration = duration_cast<nanoseconds>(nowTime - beginTime);
	dbTime = duration.count() / 1000000000.0;
	unscaledTime = static_cast<float>(dbTime);

	deltaTime = unscaledDeltaTime * timeScale;
	time += deltaTime;

	lastTime = nowTime;
}