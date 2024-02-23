#pragma once
#include <string>
#include "Frame.h"
#include "Color.h"
namespace df {
	class Sprite {

	private:
		int width;                    // Sprite width.
		int height;                   // Sprite height.
		int max_frame_count;          // Maximum number of frames sprite can have.
		int frame_count;              // Actual number of frames sprite has.
		Color color;                  // Optional color for entire sprite.
		int slowdown;        	    // Animation slowdown (1=no slowdwn, 0=stop).
		Frame* frame;                 // Array of frames.
		std::string label;            // Text label to identify sprite.
		Sprite();                     // Sprite constructor always has one arg.
		char transparency;			 //Character that represents transparancy 

	public:
		// Destroy sprite, deleting any allocated frames.
		~Sprite();

		// Create sprite with indicated maximum number of frames.
		Sprite(int max_frames);

		// Set width of sprite.
		void setWidth(int new_width);

		// Get width of sprite.
		int getWidth() const;

		// Set height of sprite.
		void setHeight(int new_height);

		// Get height of sprite.
		int getHeight() const;

		// Set sprite color.
		void setColor(Color new_color);

		// Get sprite color.
		Color getColor() const;

		// Get total count of frames in sprite.
		int getFrameCount();

		// Add frame to sprite.
		// Return -1 if frame array full, else 0.
		int addFrame(Frame new_frame);

		// Get next sprite frame indicated by number.
		// Return empty frame if out of range [0, frame_count].
		Frame getFrame(int frame_number) const;

		// Set label associated with sprite.
		void setLabel(std::string new_label);

		// Get label associated with sprite.
		std::string getLabel() const;

		// Set animation slowdown value.
		// Value in multiples of GameManager frame time.
		void setSlowdown(int new_sprite_slowdown);

		// Get animation slowdown value.
		// Value in multiples of GameManager frame time.
		int getSlowdown() const;

		// Draw indicated frame centered at position (x,y).
		// Return 0 if ok, else -1.
		// Note: top-left coordinate is (0,0).
		int draw(int frame_number, Vector position) const;

		//Sets transparency character
		void setTransparency(char newTrans);

		//Gets transparency character
		char getTransparency();
	};

}