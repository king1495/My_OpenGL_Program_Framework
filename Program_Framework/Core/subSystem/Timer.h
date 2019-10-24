#pragma once
#include "ISubSystem.h"

class Timer final : public ISubSystem
{
public:
	static Timer& GetInstance() {
		static Timer* _instance = new Timer();
		return *_instance;
	}

	void Update() {
		_currentTime = glfwGetTime();
		_elapsedTime = _currentTime - _oldTime;
		_oldTime = _currentTime;
	};

	inline float GetElapsedTime(void) const { return _elapsedTime; }
	inline float GetTime(void) const { return _currentTime; }
	inline float GetFPS(void) { return 1.f / _elapsedTime; }

private:
	double _oldTime;
	double _currentTime;
	double _elapsedTime;

	Timer()
		:_oldTime(0), _elapsedTime(0), _currentTime(0)
	{};
};

#define _Timer Timer::GetInstance()