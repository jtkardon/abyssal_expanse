#include "Harpoon.h"
#include "EventStep.h"
#include "EventSub.h"
#include "WorldManager.h"
#include "EventAfterUpdate.h"
#include "LogManager.h"
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


int Harpoon::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == AFTER_UPDATE_EVENT) {
		if (sub->getDirFacing() == 1)
			setSprite("harpoonRight");
		else
			setSprite("harpoonLeft");
		if (x_offset < 12 && !goingBack)
			x_offset += 2;
		else {
			goingBack = true;
			x_offset -= 2;
		}
		df::Vector newPos = df::Vector(sub->getPosition().getX() + x_offset * sub->getDirFacing(), sub->getPosition().getY() + 0.75);
		WM.moveObject(this, newPos);
		if (x_offset < 4)
			WM.markForDelete(this);
		return 1;
	} 
	return 0;
}



