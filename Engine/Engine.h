#pragma once

class Engine // static class
{
private: 
	Engine();

public:
	static void Start();
	static void Exit();

private:
	static constexpr double fixedSleepTime = 16;

	static bool exited;

	static void InitializeStatics();
	static void Run();
	static void Update();
	static void CountFps(double);
};

