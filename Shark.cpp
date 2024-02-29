#include "Shark.h"
#include "EventStep.h"
#include "EventSub.h"
#include "WorldManager.h"
#include "EventView.h"
#include "ViewObject.h"
#include "LogManager.h"
#include <iostream>
#include "ResourceManager.h"

Shark::Shark(df::Vector pos)
{
	setType("shark");
	setSprite("sharkRight");
	setSpeed(.5);
	setSolidness(df::SOFT);
	setAltitude(2);
	setPosition(pos);
	health = 2;
	weaponHitByID = -1;
	changedSpeed = 0.5;
}

Shark::~Shark() {
	df::EventView ev("Score", 10, true);
	WM.onEvent(&ev);
	df::Sound* dieSound = RM.getSound("dieShark");
	dieSound->play();
}

//Listen for sub, step, collision events
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

//Every 3 frames, make the shark move towards the player
void Shark::step(int count) {
	if (count % 3 == 0) {
		df::Vector newDir = df::Vector((sub->getPosition().getX() - getPosition().getX()), (sub->getPosition().getY() - getPosition().getY()));
		newDir.normalize();
		setDirection(newDir);
		setSpeed(changedSpeed);
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

//Handle sharks collisions
void Shark::collide(const df::EventCollision* p_collision_event)
{
	if (p_collision_event->getObject1()->getType() == "weapon" ||
		p_collision_event->getObject2()->getType() == "weapon") {

		//Make sure the shark isn't hit by the same weapon twice
		if (p_collision_event->getObject1()->getType() == "weapon") {
			if (weaponHitByID == p_collision_event->getObject1()->getId()) //If already hit by this weapon, ignore the collision
				return;
			//If new weapon, then store id
			weaponHitByID = p_collision_event->getObject1()->getId();
		}
		else {
			if (weaponHitByID == p_collision_event->getObject2()->getId()) //If already hit by this weapon, ignore the collision
				return;
			//If new weapon, then store id
			weaponHitByID = p_collision_event->getObject2()->getId();
		}
		df::Sound* hitSound = RM.getSound("hitShark");
		hitSound->play();
		health--;
		//If shark's health is 0, delete and increment score
		if (health == 0) {
			WM.markForDelete(this);
		}
		else { //Change color of shark to red if got hit but didn't die
			changedSpeed = 0.75;
			if (getDirection().getX() > 0)
				setSprite("sharkRightRed");
			else
				setSprite("sharkLeftRed");
		}
	}
	//Harpoon one shots shark
	else if (p_collision_event->getObject1()->getType() == "harpoon" ||
		p_collision_event->getObject2()->getType() == "harpoon") {
		WM.markForDelete(this);
	}
}

