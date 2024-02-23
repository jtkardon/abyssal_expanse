#pragma once
#include <string>
#include "Sprite.h"
#include "Box.h"

namespace df {
	class Animation {

	private:
		Sprite* m_p_sprite;    // Sprite associated with Animation.
		std::string m_name;    // Sprite name in ResourceManager.
		int m_index;           // Current index frame for Sprite.
		int m_slowdown_count;  // Slowdown counter.

	public:
		// Animation constructor
		Animation();

		// Set associated Sprite to new one.
		// Note, Sprite is managed by ResourceManager.
		// Set Sprite index to 0 (first frame).
		void setSprite(Sprite* p_new_sprite);

		// Return pointer to associated Sprite.
		Sprite* getSprite() const;
		// Set Sprite name (in ResourceManager).
		void setName(std::string new_name);

		// Get Sprite name (in ResourceManager).
		std::string getName() const;

		// Set index of current Sprite frame to be displayed.
		void setIndex(int new_index);

		// Get index of current Sprite frame to be displayed.
		int getIndex() const;

		// Set animation slowdown count (-1 means stop animation).
		void setSlowdownCount(int new_slowdown_count);

		// Set animation slowdown count (-1 means stop animation).
		int getSlowdownCount() const;

		// Draw single frame centered at position (x,y).
		// Drawing accounts for slowdown, and advances Sprite frame.
		// Return 0 if ok, else -1.
		int draw(Vector position);

		//Get bounding box of associated Sprite
		Box getBox() const;
	};

}