#include "Clock.h"
#include "Windows.h"

using namespace df;
// Sets previous_time to current time.
Clock::Clock()
{
	previous_time = getCurrentTime();
}


// Return time elapsed since delta() was last called, -1 if error.
// Units are microseconds.
long int Clock::delta(void)
{
	if (!previous_time) {
		return -1;
	}
	long int currTime = getCurrentTime();
	long int elapsed = currTime - previous_time;
	previous_time = currTime;
	return elapsed;
}

// Return time elapsed since delta() was last called.
// Units are microseconds.
long int Clock::split(void) const
{
	if (!previous_time) {
		return -1;
	}
	return getCurrentTime() - previous_time;
}

//Gets the current time for Windows
long int Clock::getCurrentTime() const {
	SYSTEMTIME time;
	GetSystemTime(&time);
	return (time.wDay * 24 * 60 * 60 * 1000000)
		 + (time.wHour * 60 * 60 * 1000000)
		+ (time.wMinute * 60 * 1000000)
		+ (time.wSecond * 1000000)
		+ (time.wMilliseconds * 1000);
}
