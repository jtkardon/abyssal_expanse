#include "EventStep.h"

// Default constructor
df::EventStep::EventStep()
{
	setType(STEP_EVENT);
	step_count = 0;
}

//Constructor with initial step count
df::EventStep::EventStep(int init_step_count)
{
	setType(STEP_EVENT);
	step_count = init_step_count;
}


//Set step count
void df::EventStep::setStepCount(int new_step_count)
{
	step_count = new_step_count;
}

// Get step count
int df::EventStep::getStepCount() const
{
	return step_count;
}
