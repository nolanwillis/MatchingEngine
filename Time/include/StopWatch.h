#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include "TimeAmount.h"

/*
Class that acts as a stopwatch. Call Start() to record the current time as the startTime. 
Call Stop() to get the TimeAmount that passed between the startTime and the new current time.
*/
class StopWatch
{
public:
	StopWatch();
	StopWatch(const StopWatch& rhs) = delete;
	StopWatch &operator = (const StopWatch& rhs) = delete;
	~StopWatch() = default;

	// Marks the moment in time that Stop() will get measured against.
	void Start();
	// Returns the amount of time that has elapsed since Start() was called.
	const TimeAmount Stop() const;

private:
	TimeAmount startTime;
	
	static const TimeAmount GetSystemTime();
};

#endif
