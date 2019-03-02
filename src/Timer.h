#pragma once

#include "apollo.h"
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock Clock;

class Timer
{
private:
	high_resolution_clock::time_point timeLastFrame;
	milliseconds deltaTime;
	int framesPerSecond;
	float framePerSecondLimit = 30.0f;
	float skipTick = 1000.0f / framePerSecondLimit;
	
	void calculateFramesPerSecond();
	
public:
	API_INTERFACE void start();
	API_INTERFACE void update();

	API_INTERFACE inline long long getElapsedTime();
	API_INTERFACE int getFramesPerSecond();

	API_INTERFACE inline float getFramePerSecondLimit();
	API_INTERFACE inline void setFramePerSecondLimit(float limit);

	API_INTERFACE float getSkipTick();
};

