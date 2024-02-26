#include "Harpoon.h"
#include "EventStep.h"
#include "EventSub.h"
#include "WorldManager.h"
#include "EventAfterUpdate.h"
#include "LogManager.h"

//Harpoon pierces through enemies and isn't delete when it hits one
Harpoon::Harpoon(Sub* sub)
{
	setType("harpoon");
	if (sub->getDirFacing() == 1)
		setSprite("harpoonRight");
	else
		setSprite("harpoonLeft");
	setAltitude(1);
	setSolidness(df::SOFT);
	setPosition(sub->getPosition());
	x_offset = 4;
	this->sub = sub;
	goingBack = false;
}

//Handles after update event
int Harpoon::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == AFTER_UPDATE_EVENT) {
		//Every frame make sure using correct sprite
		if (sub->getDirFacing() == 1)
			setSprite("harpoonRight");
		else
			setSprite("harpoonLeft");

		//first increment x_offset
		//Then decremenet it
		if (x_offset < 12 && !goingBack)
			x_offset += 2;
		else {
			goingBack = true;
			x_offset -= 2;
		}
		//Every frame move the object to the location of the sub
		//Use x_offset to move the harpoon horizontally
		//mulitply it by the direction of the sub to flip if facing other direction
		df::Vector newPos = df::Vector(sub->getPosition().getX() + x_offset * sub->getDirFacing(), sub->getPosition().getY() + 0.75);
		WM.moveObject(this, newPos);
		//Delete harpoon once finished
		if (x_offset < 4)
			WM.markForDelete(this);
		return 1;
	} 
	return 0;
}



