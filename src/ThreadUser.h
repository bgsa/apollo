#pragma once

#include "apollo.h"
#include <thread>
#include <chrono>

class ThreadUser
{
private:
	std::thread* instance;
	bool isRunning = false;
	
public:
	void start();
	void stop();
	void sleep(size_t miliseconds);
	virtual void run() = 0;
	void join();
	void detach();

	std::thread::id getId();

	~ThreadUser();
};

