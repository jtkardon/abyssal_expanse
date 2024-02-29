#include "GameStart.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Generator.h"
#include "EventKeyboard.h"
#include "GameManager.h"

GameStart::GameStart()
{
	setAltitude(1);
	setSprite("title");
	titleMusic = RM.getMusic("titleMusic");
	titleMusic->play();
	WM.setViewPosition(df::Vector());

	//Puts sprite in middle of screen
	df::Vector p(WM.getView().getHorizontal() * 3 / 6,
		WM.getView().getVertical() / 2);
	setPosition(p);
}

//Handles keyboard events
int GameStart::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::ENTER:
				new Generator();
				WM.markForDelete(this);
				titleMusic->stop();
				break;
			case df::Keyboard::Q:
				GM.setGameOver();
				titleMusic->stop();
				break;
		}
	}
	return 0;
}
