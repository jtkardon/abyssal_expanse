#include "Bubble.h"
#include <stdlib.h>
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "LogManager.h"

Bubble::Bubble(bool first)
{

	setType("bubble");
	setSolidness(df::SPECTRAL);

	setAltitude(0);
	char bubbleChars[] = { 'o', '0', 'O', '°' };
	bubbleChar = bubbleChars[rand() % 4];
	
	if (first) {
		setVelocity(df::Vector(0, (float)-1.0 / (rand() % 10 + 1)));
		df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
			(float)(rand() % (int)WM.getBoundary().getVertical()));
		setPosition(p);
	}
	else {
		setVelocity(df::Vector(0, (float)-1.0 / (rand() % 10 + 1)));
		//df::Vector p;
		df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)((WM.getView().getVertical() + WM.getView().getCorner().getY()) + rand() % 20));
	
		setPosition(p);
	}

}

int Bubble::draw()
{
	//LM.writeLog("DRAw\n");
	return DM.drawCh(getPosition(), bubbleChar, df::BLUE);
}

int Bubble::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT) {
		new Bubble(false);
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}
