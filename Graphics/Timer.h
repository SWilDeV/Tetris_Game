#ifndef TIMER_H_
#define TIMER_H_

#include "SDL.h"

class Timer
{
public:
	Timer();
	~Timer();
	
	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:

	static Timer* sInstance;
	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltatime;
	float mTimeScale;
};

#endif // !_TIMER_H_

