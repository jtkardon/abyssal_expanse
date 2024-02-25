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
