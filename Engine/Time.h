#pragma once

#include <chrono>

class Time // static class
{
private:
	Time();

public:
	static float deltaTime;
	static float time;

	static double dbDeltaTime;
	static double dbTime;

	static float unscaledDeltaTime;
	static float unscaledTime;

	static float timeScale;

	static void Update();
	static void Init();

private:
	static std::chrono::steady_clock::time_point beginTime;
	static std::chrono::steady_clock::time_point lastTime;
};

