#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

#include "Event.h"

namespace df {


	const std::string STEP_EVENT = "df::step";

	class EventStep : public df::Event {
	private:
		int step_count; // Iteration number of game loop.

	public:
		EventStep(); // Default constructor
		EventStep(int init_step_count); //Constructor with initial step count
		void setStepCount(int new_step_count); //Set step count
		int getStepCount() const; //Get step count
	};
}
#endif
