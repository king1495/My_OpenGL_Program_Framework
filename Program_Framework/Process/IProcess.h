#pragma once
#include <mutex>
#include <thread>
#include <future>

class IProcess
{
public:
	IProcess()
		:isRun(false), currentLoop(0), maxLoop(0)
	{}
	virtual ~IProcess() { Stop(); }

	bool Run()
	{
		if (isRun) return false;
		t_job = std::thread([&]() {ThreadProcess(); });
		return true;
	}

	void Stop()
	{
		isRun = false;
		if (t_job.joinable()) t_job.join();
	}

	bool isRunning() { return isRun; };
	float GetProgress() { return (float)currentLoop / (float)maxLoop; };

protected:
	std::thread t_job;
	std::mutex m_job;

	bool isRun;

	unsigned int currentLoop;
	unsigned int maxLoop;

	virtual void ThreadProcess() {
		if (isRun) return;
		isRun = true;
		currentLoop = 0;
		maxLoop = 0;
		PreProcess();
		while (isRun)
		{
			std::unique_lock<std::mutex> lock(m_job);
			MainProcess();
			lock.unlock();
			currentLoop++;
			if ((maxLoop != 0) & (currentLoop >= maxLoop)) isRun = false;
		}
		PostProcess();
		isRun = false;
	}

	virtual void PreProcess() = 0;
	virtual void MainProcess() = 0;
	virtual void PostProcess() = 0;
};