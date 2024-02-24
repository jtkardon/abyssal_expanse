#include "Sub.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "LogManager.h"

Sub::Sub()
{
	setSprite("rightSub");
	setSolidness(df::SOFT);
	setType("sub");
	//Increase size of world to 4 times the size
	WM.setBoundary(df::Box(df::Vector(), DM.getHorizontal() * 2, DM.getVertical() * 2));
	//WM.setViewFollowing(this);
	//setPosition(df::Vector(7, 2));
	setPosition(df::Vector(50, 5));
	//setSpeed(1);
	
}

Sub::~Sub() {
	GM.setGameOver();
}

//Listen for keyboard events
int Sub::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		keyHandler(p_keyboard_event);
		return 1;
	}
	else if (p_e->getType() == df::STEP_EVENT) {
		//If stays on window, allow move	

	}
	return 0;
}

// Take appropriate action according to key pressed
void Sub::keyHandler(const df::EventKeyboard * p_keyboard_event)
{
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q: // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;
	case df::Keyboard::W: // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveY(-0.55);
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(getDirection().getX(), 0));
		}
		break;
	case df::Keyboard::S: // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			moveY(0.55);
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(getDirection().getX(), 0));
		}
		break;
	case df::Keyboard::A: // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			setSprite("leftSub");
			moveX(-1.5);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(0, getDirection().getY()));
		}
		break;
	case df::Keyboard::D: // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			moveX(1.5);
			setSprite("rightSub");
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(0, getDirection().getY()));
		}
		break;
	}
}

//Moves the sub the given distance in the X direction
void Sub::moveX(float delta)
{

	df::Vector new_pos(getPosition().getX() + delta, getPosition().getY());
	if ((new_pos.getX() > 6) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal() - 1)) {
		setVelocity(df::Vector(delta, getDirection().getY()));
	}
	else {
		setVelocity(df::Vector(0, getDirection().getY()));
	}
	
}


void Sub::moveY(float delta) {
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + delta);
	if ((new_pos.getY() > 1) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1)) {
		setVelocity(df::Vector(getDirection().getX(), delta));
	}
	else {
		setVelocity(df::Vector(getDirection().getX(), 0));
	}
}

