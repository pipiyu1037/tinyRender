#include "Engine.h"
#include "MessageOut.h"
#include "Time.h"
#include "GOManager.h"
#include "RenderBase.h"
#include "Input.h"
#include "MeshLoader.h"

#include <thread>
#include <iostream>
#include <chrono>

#include <Windows.h>
#include <timeapi.h>

#pragma comment(lib, "winmm.lib")

bool Engine::exited = false;

void Engine::Start() {
	
	InitializeStatics();

	Run();
}

void Engine::Exit() {
	exited = true;
}

void Engine::InitializeStatics() {
	MessageOut::OpenLog("Log.txt");
	Time::Init();
	RenderBase::Init();
	MeshLoader::Load();
	Input::Init(RenderBase::window);
}

void Engine::Run() {
	using namespace std::chrono;

	static double timeCorrection = 0;
	static auto lastTime = steady_clock::now();

	while (!exited) {
		CountFps(Time::dbDeltaTime * 1000.0);

		auto nowTime = steady_clock::now();
		auto duration = duration_cast<nanoseconds>(nowTime - lastTime);
		double miliDuraion = duration.count() / 1000000.0;

		int sleepTime = fixedSleepTime - static_cast<int>(miliDuraion);

		/*if (sleepTime > 0)
			MessageOut::Console << sleepTime << std::endl;*/

		if (sleepTime >= 5) {
			timeBeginPeriod(1);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime - 3));
			timeEndPeriod(1);
		}

		nowTime = steady_clock::now();
		duration = duration_cast<nanoseconds>(nowTime - lastTime);
		miliDuraion = duration.count() / 1000000.0;

		while (miliDuraion + timeCorrection < fixedSleepTime) {
			SwitchToThread();
			nowTime = steady_clock::now();
			duration = duration_cast<nanoseconds>(nowTime - lastTime);
			miliDuraion = duration.count() / 1000000.0;
		}

		if (timeCorrection > 1.5) {
			timeCorrection = 1.5;
		}
		timeCorrection += miliDuraion - fixedSleepTime;
		
		lastTime = nowTime;

		Update();
	}
}

void Engine::Update() {
	Time::Update();
	Input::Update();
	GOManager::Update();
	ROManager::Render();
}

void Engine::CountFps(double miliDuration) {
	static double duration = 0;
	static int fps = 0;

	duration += miliDuration;
	++fps;

	if (duration >= 1000.0) {
		duration -= 1000.0;
		if (duration >= 500.0) {
			duration = 0.0;
		}
		MessageOut::Console << "    fps:" << fps << std::endl;
		fps = 0;
	}
}