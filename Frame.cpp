#include "Frame.h"
#include "DisplayManager.h"
#include "LogManager.h"
// Create empty frame.
df::Frame::Frame()
{
}

// Create frame of indicated width and height with string.
df::Frame::Frame(int new_width, int new_height, std::string frame_str)
{
	width = new_width;
	height = new_height;
	this->frame_str = frame_str;
}


// Set width of frame.
void df::Frame::setWidth(int new_width)
{
	width = new_width;
}

// Get width of frame.
int df::Frame::getWidth() const
{
	return width;
}

// Set height of frame.
void df::Frame::setHeight(int new_height)
{
	height = new_height;
}

// Get height of frame.
int df::Frame::getHeight() const
{
	return height;
}

// Set frame characters (stored as string).
void df::Frame::setString(std::string new_frame_str)
{
	frame_str = new_frame_str;
}

// Get frame characters (stored as string).
std::string df::Frame::getString() const
{
	return frame_str;
}

// Draw self centered at position (x,y) with color.
// Don't draw transparent characters (0 means none). Return 0 if ok, else -1.
int df::Frame::draw(Vector position, Color color, char transparency) const
{
	// Error check empty string.
	if (frame_str.empty())
		return -1;

	// Determine offset since centered
	double x_offset = width / 2;
	double y_offset = height / 2;


	// Draw row by row, character by character.
	for (int y = 0; y < height; y++) {	
		for (int x = 0; x < width; x++) {
			if (transparency == NULL || (frame_str[y * width + x] != transparency)) {
				Vector temp_pos(position.getX() - x_offset + x,
					position.getY() - y_offset + y);
				DM.drawCh(temp_pos, frame_str[y * width + x], color);
			}
		}
	}
	return 0;

}
