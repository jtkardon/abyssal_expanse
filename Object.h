#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include "Vector.h"
#include "Event.h"
#include "Color.h"
#include "Animation.h"
#include "Box.h"

namespace df {
	enum Solidness {
		HARD,     // Objects cause collisions and impede.
		SOFT,     // Objects cause collisions, but don't impede.
		SPECTRAL  // Objects don't cause collisions.
	};

	class Object {

	private:
		int id;            // Unique Object identifier.
		std::string type;  // User-defined identification.
		Vector pos;        // Position in game world.
		int altitude;
		Color color;
		Vector direction; //Direction vector
		float speed;
		Solidness solidness; //Solidness of object
		Animation animation; //Animation associated with Object
		Box box; //Box for sprite boundary & collisions

	public:
		Object();
		virtual ~Object();

		// Set object id.
		void setId(int new_id);

		// Get object id.
		int getId() const;

		// Set type identifier of Object.
		void setType(std::string new_type);

		// Get type identifier of Object.
		std::string getType() const;

		// Set position of object.
		void setPosition(Vector new_pos);

		// Get position of object.
		Vector getPosition() const;

		// Handle event 
		// Return 0 if ignored, else 1.
		virtual int eventHandler(const Event* p_event);

		//Draws the current object to screen
		virtual int draw();

		// Set object altitude.
		// Checks for in range [0, MAX_ALTITUDE].
		// Return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Return object altitude.
		int getAltitude() const;

		// Set speed of Object.
		void setSpeed(float speed);

		// Get speed of Object.
		float getSpeed() const;

		// Set direction of Object.
		void setDirection(Vector new_direction);

		// Get direction of Object.
		Vector getDirection() const;

		// Set direction and speed of Object.
		void setVelocity(Vector new_velocity);

		// Get velocity of Object based on direction and speed.
		Vector getVelocity() const;

		// Predict Object position based on speed and direction.
		// Return predicted position. 
		Vector predictPosition();

		// True if HARD or SOFT, else false.
		bool isSolid() const; 

		// Set object solidness, with checks for consistency.
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return object solidness.
		Solidness getSolidness() const;

		//Set the sprite of the object to animate
		//Return 0 if ok, else -1
		int setSprite(std::string sprite_label);

		//Set animation for this Object to new one
		//Set bounding box to size of associated Sprite
		void setAnimation(Animation new_animation);

		//Get Animation for this Object
		Animation getAnimation() const;

		//Sets the animation cooldown
		void setAnimationCooldown(int newSlowdown);

		// Set object's bounding box.
		void setBox(Box new_box);

		// Get object's bounding box.
		Box getBox() const;
	};
} 
#endif