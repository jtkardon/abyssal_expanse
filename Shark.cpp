#include "Shark.h"
#include "EventStep.h"
#include "EventSub.h"
#include "WorldManager.h"
#include "EventView.h"
#include "ViewObject.h"
#include "LogManager.h"
#include <iostream>

Shark::Shark(df::Vector pos)
{
	setType("shark");
	setSprite("sharkRight");
	setPosition(pos);
	setSpeed(.5);
	setSolidness(df::SOFT);
	setAltitude(1);
	health = 2;
	weaponHitByID = -1;
}

//Listen for sub, step events
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
		return 1;
	}
	else if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
	}
	return 0;
}

//Every frame, make the shark move towards the player
void Shark::step(int count) {
	if (count % 3 == 0) {
		df::Vector newDir = df::Vector((sub->getPosition().getX() - getPosition().getX()), (sub->getPosition().getY() - getPosition().getY()));
		setDirection(newDir);
		setSpeed(0.5);
		if (newDir.getX() > 0) //Moving right
		{
			if (health == 2)
				setSprite("sharkRight");
			else
				setSprite("sharkRightRed");
		}
		else { //Moving left
			if (health == 2)
				setSprite("sharkLeft");
			else
				setSprite("sharkLeftRed");
		}
	}
}

void Shark::collide(const df::EventCollision* p_collision_event)
{
	if (p_collision_event->getObject1()->getType() == "weapon" ||
		p_collision_event->getObject2()->getType() == "weapon") {

		//Make sure the shark isn't hit by the same weapon twice
		if (p_collision_event->getObject1()->getType() == "weapon") {
			if (weaponHitByID == p_collision_event->getObject1()->getId()) //If already hit by this weapon, ignore the collision
				return;
			weaponHitByID = p_collision_event->getObject1()->getId();
		}
		else {
			if (weaponHitByID == p_collision_event->getObject2()->getId()) //If already hit by this weapon, ignore the collision
				return;
			weaponHitByID = p_collision_event->getObject2()->getId();
		}


		health--;
		if (health == 0)
			WM.markForDelete(this);
		else { //Change color of shark to red if got hit
			if (getDirection().getX() > 0)
				setSprite("sharkRightRed");
			else
				setSprite("sharkLeftRed");
		}
	}
}

