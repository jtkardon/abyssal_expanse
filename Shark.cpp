#include "Shark.h"
#include "EventStep.h"
#include "EventSub.h"


Shark::Shark(df::Vector pos)
{
	setType("shark");
	setSprite("sharkRight");
	setPosition(pos);
	setSpeed(.5);
	setSolidness(df::SOFT);
	setAltitude(1);
}

int Shark::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step_event =
			dynamic_cast <const df::EventStep*> (p_e);
		step(p_step_event->getStepCount());
		return 1;
	}
	else if (p_e->getType() == SUB_EVENT) {
		const EventSub* p_sub_event =
			dynamic_cast <const EventSub*> (p_e);
		sub = p_sub_event->getSub();
		
	}
	return 0;
}

void Shark::step(int count) {
	if (count % 3 == 0) {
		df::Vector newDir = df::Vector((sub->getPosition().getX() - getPosition().getX()), (sub->getPosition().getY() - getPosition().getY()));
		setDirection(newDir);
		setSpeed(0.5);
		if (newDir.getX() > 0) //Moving right
			setSprite("sharkRight");
		else { //Moving left
			setSprite("sharkLeft");
		}
	}
}
