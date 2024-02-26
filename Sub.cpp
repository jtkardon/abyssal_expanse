#include "Sub.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Laser.h"
#include "Shark.h"
#include "EventSub.h"
#include "ViewObject.h"
#include "EventView.h"
#include "Spawner.h"
#include "Harpoon.h"

Sub::Sub()
{
	setSprite("rightSub");
	setType("sub");
	//Increase size of world to 4 times the size
	WM.setBoundary(df::Box(df::Vector(), DM.getHorizontal() * 2, DM.getVertical() * 2));
	WM.setViewFollowing(this);
	setPosition(df::Vector(7, 5));
	setAltitude(2);
	dirFacing = 1;
	laser_slowdown = 15;
	laser_countdown = 0;
	harpoon_slowdown = 30;
	harpoon_countdown = 0;
	health = 3;

	//Creates health view object
	df::ViewObject* healthView = new df::ViewObject;
	healthView->setLocation(df::TOP_LEFT);
	healthView->setViewString("Health");
	healthView->setValue(health);
	healthView->setColor(df::RED);

	//Creates score view object
	df::ViewObject* points = new df::ViewObject;
	points->setLocation(df::TOP_RIGHT);
	points->setViewString("Score");
	points->setColor(df::GREEN);
}


Sub::~Sub() {
	GM.setGameOver();
}

//Listen for keyboard, mouse, step events
int Sub::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		keyHandler(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::MOUSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouseHandler(p_mouse_event);
		return 1;
	}
	else if (p_e->getType() == df::STEP_EVENT) {
		laser_countdown--;
		harpoon_countdown--;
		EventSub es(this);
		WM.onEvent(&es);
		return 1;
	}
	else if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
		return 1;
	}
	return 0;
}

// Take appropriate action according to key pressed
// Q - quit
// WASD - move sub
// Pressing one of WASD will set velocity of sub
// Releasing will set velocity to 0;
// AD also change the subs sprite 
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
			dirFacing = -1;
			setSprite("leftSub");
			moveX(-1.5);
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(0, getDirection().getY()));
		}
		break;
	case df::Keyboard::D: // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			dirFacing = 1;
			moveX(1.5);
			setSprite("rightSub");
		}
		else if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			setDirection(df::Vector(0, getDirection().getY()));
		}
		break;
	}
}

//Handles mouse events
void Sub::mouseHandler(const df::EventMouse* p_mouse_event)
{

	if (p_mouse_event->getMouseAction() == df::PRESSED) {

		if (p_mouse_event->getMouseButton() == df::Mouse::LEFT) { //Laser
			fireLaser();
		}
		else if (p_mouse_event->getMouseButton() == df::Mouse::RIGHT) { //Harpoon
			if (harpoon_countdown > 0)
				return;
			harpoon_countdown = harpoon_slowdown;
			new Harpoon(this);
		}
	}
	
}

//Creates laser object and sets its velocity depending on direction of the sub
void Sub::fireLaser()
{
	if (laser_countdown > 0)
		return;
	laser_countdown = laser_slowdown;
	//Set speed of laser to 5
	df::Vector dir = df::Vector(dirFacing, 0);
	dir.normalize();
	dir.scale(5);
	Laser* laser = new Laser();
	laser->setVelocity(dir);
	
	if (dirFacing == 1) { //Facing right
		df::Vector new_pos = df::Vector(getPosition().getX() + 7, getPosition().getY() + 1);
		laser->setPosition(new_pos);
		laser->setSprite("laserRight");
	}
	else { //Facing left
		df::Vector new_pos = df::Vector(getPosition().getX() - 7, getPosition().getY() + 1);
		laser->setPosition(new_pos);
		laser->setSprite("laserLeft");
	}
}



//Moves the sub the given distance in the X direction
void Sub::moveX(float delta)
{
	//If stays on window, allow move	
	df::Vector new_pos(getPosition().getX() + delta, getPosition().getY());
	if ((new_pos.getX() > 6) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal() - 6)) {
		setVelocity(df::Vector(delta, getDirection().getY()));
	}
	else {
		setVelocity(df::Vector(0, getDirection().getY()));
	}
	
}

//Moves the sub the given distance in the Y direction
void Sub::moveY(float delta) {

	//If stays on window, allow move	
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + delta);
	if ((new_pos.getY() > 1) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 2)) {
		setVelocity(df::Vector(getDirection().getX(), delta));
	}
	else {
		setVelocity(df::Vector(getDirection().getX(), 0));
	}
}

//Manages any collisions with the sub
void Sub::collide(const df::EventCollision* p_collision_event)
{
	//Only check object1 to prevent double collisions
	if (p_collision_event->getObject1()->getType() == "shark") {
		WM.markForDelete(p_collision_event->getObject1());
		health--;
		if (health < 0) {
			health = 0;
		}
		df::EventView ev("Health", health, false);
		WM.onEvent(&ev);
		if (health == 0) {
			WM.markForDelete(this);
		}
	}
	//Only check object2 to prevent double collisions
	else if (p_collision_event->getObject2()->getType() == "coin") {
		WM.markForDelete(p_collision_event->getObject2());
		df::EventView ev("Score", 20, true);
		WM.onEvent(&ev);
	}

}

//Gets direction facing
int Sub::getDirFacing() {
	return dirFacing;
}
