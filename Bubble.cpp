#include "Bubble.h"
#include <stdlib.h>
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "LogManager.h"

//First boolean detemines whether the bubble is spawned in at the start of the game or while it is running
//If true, bubbles can spawn on the screen
//If false, bubbles will only spawn off screen
Bubble::Bubble(bool first)
{

	setType("bubble");
	setSolidness(df::SPECTRAL);

	setAltitude(0);
	//Randomizes what character the bubble is
	char bubbleChars[] = { 'o', '0', 'O', '°' };
	bubbleChar = bubbleChars[rand() % 4];
	
	if (first) { //Spawn in the entire world
		setVelocity(df::Vector(0, (float)-1.0 / (rand() % 10 + 1)));
		df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
			(float)(rand() % (int)WM.getBoundary().getVertical()));
		setPosition(p);
	}
	else { //Spawn not on screen
		setVelocity(df::Vector(0, (float)-1.0 / (rand() % 10 + 1)));
		df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)((WM.getView().getVertical() + WM.getView().getCorner().getY()) + rand() % 20));
	
		setPosition(p);
	}

}

//Overrides draw function to just draw a character
int Bubble::draw()
{
	return DM.drawCh(getPosition(), bubbleChar, df::BLUE);
}

// Checks for out event
int Bubble::eventHandler(const df::Event* p_e)
{
	//When goes out, delete object and create new bubble
	if (p_e->getType() == df::OUT_EVENT) {
		new Bubble(false);
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}
