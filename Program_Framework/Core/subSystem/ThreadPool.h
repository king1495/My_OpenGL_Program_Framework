#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include "ISubSystem.h"

class ThreadPool final : public ISubSystem
{
public:
	static ThreadPool& GetInstance() {
		static ThreadPool* _instance = new ThreadPool();
		return *_instance;
	}

	template<class F, class...Args>
	std::future<typename std::result_of<F(Args...)>::type> EnqueueTask(F&& f, Args&&... args);

private:
	ThreadPool(size_t _size = std::thread::hardware_concurrency() - 1);
	~ThreadPool();

	void WorkerThread()
	{
		while (true) {
			std::unique_lock<std::mutex> lock(mutex_task);

			cv_task.wait(lock, [this] { return !this->tasks.empty() || stop_all; });
			if (stop_all && this->tasks.empty()) return;

			std::function<void()> task = std::move(tasks.front());
			tasks.pop();
			lock.unlock();

			task();
		}
	}

	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;

	std::mutex mutex_task;
	std::condition_variable cv_task;
	bool stop_all;
};

ThreadPool::ThreadPool(size_t _size)
	: stop_all(false)
{
	workers.reserve(_size);
	for (size_t i = 0; i < _size; ++i)
		workers.emplace_back([this]() {this->WorkerThread(); });
}

template<class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueTask(F&& f, Args&&... args)
{
	if (stop_all)
		throw std::runtime_error("ThreadPool on stopped!!");

	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> result = task->get_future();
	{
		std::unique_lock<std::mutex> lock(mutex_task);
		tasks.emplace([task]() { (*task)(); });
	}
	cv_task.notify_one();

	return result;
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(mutex_task);
		stop_all = true;
	}

	cv_task.notify_all();
	for (std::thread& worker : workers)
		worker.join();
}

#define _ThreadPool ThreadPool::GetInstance()