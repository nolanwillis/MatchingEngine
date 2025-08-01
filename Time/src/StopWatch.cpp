#include "StopWatch.h"

#include <Windows.h>
#include <profileapi.h>

StopWatch::StopWatch() 
	:
	startTime(TimeAmount::Duration::MAX)
{}

void StopWatch::Start()
{
	this->startTime = StopWatch::GetSystemTime();
}
const TimeAmount StopWatch::Stop() const
{
	TimeAmount elapsedTime;

	if (TimeAmount(TimeAmount::Duration::MAX) != this->startTime)
	{
		elapsedTime = StopWatch::GetSystemTime() - this->startTime;
	}

	return(elapsedTime);
}

const TimeAmount StopWatch::GetSystemTime()
{
	const static TimeAmount oneSecond(TimeAmount::Duration::ONE_SECOND);

	TimeAmount systemTime;

	LARGE_INTEGER counterStruct;
	LARGE_INTEGER frequencyStruct;

	if (0 != QueryPerformanceCounter(&counterStruct) && 
		0 != QueryPerformanceFrequency(&frequencyStruct))
	{
		const LONGLONG counter = counterStruct.QuadPart;
		const LONGLONG frequency = frequencyStruct.QuadPart;

		if (counter >= 0 && 0 != frequency)
		{
			const int numSeconds = static_cast<int>(counter / frequency);
			const int remainder = static_cast<int>(counter % frequency);
			systemTime = numSeconds * oneSecond;
			systemTime += (remainder / frequency) * oneSecond;
		}
	}

	return(systemTime);
}
