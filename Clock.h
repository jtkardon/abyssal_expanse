#ifndef __CLOCK_H__
#define __CLOCK_H__

// The clock, for timing (such as the game loop)
namespace df {
	class Clock {

	private:
		long int previous_time;  // Previous time delta() called (micro sec).
		long int getCurrentTime() const;

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called, -1 if error.
		// Units are microseconds.
		long int delta(void);

		// Return time elapsed since delta() was last called.
		// Units are microseconds.
		long int split(void) const;

	};
}
#endif