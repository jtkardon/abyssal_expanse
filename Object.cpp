#include "Object.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ResourceManager.h"
using namespace df;



Object::Object()
{
	static int idCounter = 0;
	id = idCounter;
	idCounter++;
	setType("Object");
	setPosition(Vector());
	altitude = 0;
	setVelocity(Vector());
	color = WHITE;
	setSolidness(HARD);
	WM.insertObject(this);
	box = Box();
}

Object::~Object()
{
	WM.removeObject(this);
}

// Set object id.
void Object::setId(int new_id)
{
	id = new_id;
}

// Get object id.
int Object::getId() const
{
	return id;
}

// Set type identifier of Object.
void Object::setType(std::string new_type)
{
	type = new_type;
}

// Get type identifier of Object.
std::string Object::getType() const
{
	return type;
}
//Set position of object.
void Object::setPosition(Vector new_pos)
{
	pos = new_pos;
}


// Get position of object.
Vector Object::getPosition() const
{
	return pos;
}

// Handle event 
// Return 0 if ignored, else 1.
int df::Object::eventHandler(const Event* p_event)
{
	//ALL TESTING CODE
	if (p_event->getType() == df::STEP_EVENT) {
		if (type == "move") {
			setVelocity(Vector(3, 1.5));
			setSpeed(0.5);
		}
		return 1;
	}
	else if (p_event->getType() == df::OUT_EVENT) {
		LM.writeLog("OUT FOR ID:%d\n", id);
	}
	else if (p_event->getType() == df::KEYBOARD_EVENT) {
		if (type == "keyboard") {
			const df::EventKeyboard* p_keyboard_event =
				dynamic_cast <const df::EventKeyboard*> (p_event);
			switch (p_keyboard_event->getKey()) {
			case df::Keyboard::W:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					Vector newPos = Vector(pos.getX(), pos.getY() - 1);
					WM.moveObject(this, newPos);
				}
				break;
			case df::Keyboard::A:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					Vector newPos = Vector(pos.getX() - 1, pos.getY());
					WM.moveObject(this, newPos);
				}
				break;
			case df::Keyboard::S:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					Vector newPos = Vector(pos.getX(), pos.getY() + 1);
					WM.moveObject(this, newPos);
				}
				break;
			case df::Keyboard::D:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
					Vector newPos = Vector(pos.getX() + 1, pos.getY());
					WM.moveObject(this, newPos);
				}
				break;
			case df::Keyboard::E:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
					Vector newPos = Vector(pos.getX() + 5, pos.getY());
					WM.moveObject(this, newPos);				}
				break;
			case df::Keyboard::Q:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
					Vector newPos = Vector(pos.getX() - 5, pos.getY());
					WM.moveObject(this, newPos);
				}
				break;
			}
		}
		return 1;
	}
	else if (p_event->getType() == df::MOUSE_EVENT) {
		if (type == "mouse") {
			const df::EventMouse* p_mouse_event =
				dynamic_cast <const df::EventMouse*> (p_event);

			if (p_mouse_event->getMouseAction() == df::PRESSED) {
				if (p_mouse_event->getMouseButton() == Mouse::Button::LEFT) {
					if (color == YELLOW) {
						color = WHITE;
					}
					else {
						color = YELLOW;
					}
				}
				else if (p_mouse_event->getMouseButton() == Mouse::Button::RIGHT) {
					if (color == RED) {
						color = WHITE;
					}
					else {
						color = RED;
					}
				}
			}
			else if (p_mouse_event->getMouseAction() == df::MOVED) {
				Vector mouseXY = p_mouse_event->getMousePosition();
				WM.moveObject(this, mouseXY);
			}
			else if (p_mouse_event->getMouseAction() == df::RELEASED) {
				if (p_mouse_event->getMouseButton() == Mouse::Button::MIDDLE) {
					if (color == MAGENTA) {
						color = WHITE;
					}
					else {
						color = MAGENTA;
					}
			}

			}
		}
		return 1;
	}
	else if (p_event->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*>(p_event);
		//LM.writeLog("Collision event between obj1:%d, obj2:%d\n", p_collision_event->getObject1()->getId(), p_collision_event->getObject2()->getId());
		color = BLUE;
	}
	return 0;
}


//Draws the current object to screen
int df::Object::draw()
{	
	return animation.draw(pos);	//LM.writeLog("Drawing this object at altitude=%d, id=%d\n", altitude, id);
}

// Set object altitude.
// Checks for in range [0, MAX_ALTITUDE].
// Return 0 if ok, else -1.
int df::Object::setAltitude(int new_altitude)
{
	if (new_altitude < 0 || new_altitude > MAX_ALTITUDE) 
		return -1;
	altitude = new_altitude;
	return 0;
}


// Return object altitude.
int df::Object::getAltitude() const
{
	return altitude;
}

// Set speed of Object.
void df::Object::setSpeed(float speed)
{
	this->speed = speed;
}

// Get speed of Object.
float df::Object::getSpeed() const
{
	return speed;
}

// Set direction of Object.
void df::Object::setDirection(Vector new_direction)
{
	new_direction.normalize();
	direction = new_direction;
}

// Get direction of Object.
Vector df::Object::getDirection() const
{
	return direction;
}

// Set direction and speed of Object.
void df::Object::setVelocity(Vector new_velocity)
{
	setSpeed(new_velocity.getMagnitude());
	Vector direction = new_velocity;
	direction.normalize();
	setDirection(direction);
}

// Get velocity of Object based on direction and speed.
Vector df::Object::getVelocity() const
{
	Vector velocity = direction;
	velocity.scale(speed);
	return velocity;
}

// Predict Object position based on speed and direction.
// Return predicted position. 
Vector df::Object::predictPosition()
{
	// Add velocity to position
	Vector new_pos = pos + getVelocity();
	return new_pos;
}

// True if HARD or SOFT, else false.
bool df::Object::isSolid() const
{
	return solidness == HARD || solidness == SOFT;
}

// Set object solidness, with checks for consistency.
// Return 0 if ok, else -1.
int df::Object::setSolidness(Solidness new_solid)
{
	return solidness = new_solid;
}

// Return object solidness.
Solidness df::Object::getSolidness() const
{
	return solidness;
}

//Set the sprite of the object to animate
//Return 0 if ok, else -1
int df::Object::setSprite(std::string sprite_label)
{
	animation.setSprite(RM.getSprite(sprite_label));
	box = animation.getBox();
	return 0;
}

//Set animation for this Object to new one
//Set bounding box to size of associated Sprite
void df::Object::setAnimation(Animation new_animation)
{
	animation = new_animation;
}

//Get Animation for this Object
Animation df::Object::getAnimation() const
{
	return animation;
}

//Sets the animation cooldown
void df::Object::setAnimationCooldown(int newSlowdown)
{
	animation.setSlowdownCount(newSlowdown);
}

// Set object's bounding box.
void df::Object::setBox(Box new_box)
{
	box = new_box;
}

// Gets object's bounding box.
Box df::Object::getBox() const
{
	return box;
}
