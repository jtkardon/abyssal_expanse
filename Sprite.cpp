#include "Sprite.h"
#include "LogManager.h"

// Destroy sprite, deleting any allocated frames.
df::Sprite::~Sprite()
{
	if (frame != NULL) {
		delete[] frame;
	}
}

// Create sprite with indicated maximum number of frames.
df::Sprite::Sprite(int max_frames)
{
	frame_count = 0;
	width = 0;
	height = 0;
	slowdown = 0;
	frame = new Frame[max_frames];
	max_frame_count = max_frames;
	color = COLOR_DEFAULT;
	transparency = NULL;
}

// Set width of sprite.
void df::Sprite::setWidth(int new_width)
{
	width = new_width;
}

// Get width of sprite.
int df::Sprite::getWidth() const
{
	return width;
}

// Set height of sprite.
void df::Sprite::setHeight(int new_height)
{
	height = new_height;
}

// Get height of sprite.
int df::Sprite::getHeight() const
{
	return height;
}

// Set sprite color.
void df::Sprite::setColor(Color new_color)
{
	color = new_color;
}

// Get sprite color.
df::Color df::Sprite::getColor() const
{
	return color;
}

// Get total count of frames in sprite.
int df::Sprite::getFrameCount()
{
	return frame_count;
}

// Add frame to sprite.
// Return -1 if frame array full, else 0.
int df::Sprite::addFrame(Frame new_frame)
{
	//Sprite full?
	if (frame_count == max_frame_count) {
		return -1;
	}
	frame[frame_count] = new_frame;
	frame_count++;
	return 0;
}

// Get next sprite frame indicated by number.
// Return empty frame if out of range [0, frame_count].
df::Frame df::Sprite::getFrame(int frame_number) const
{
	if (frame_number < 0 || frame_number >= frame_count) {
		return Frame(); //Return empty frame
	}
	return frame[frame_number];
}

// Set label associated with sprite.
void df::Sprite::setLabel(std::string new_label)
{
	label = new_label;
}

// Get label associated with sprite.
std::string df::Sprite::getLabel() const
{
	return label;
}

// Set animation slowdown value.
// Value in multiples of GameManager frame time.
void df::Sprite::setSlowdown(int new_sprite_slowdown)
{
	slowdown = new_sprite_slowdown;
}

// Get animation slowdown value.
// Value in multiples of GameManager frame time.
int df::Sprite::getSlowdown() const
{
	return slowdown;
}

// Draw indicated frame centered at position (x,y).
// Return 0 if ok, else -1.
// Note: top-left coordinate is (0,0).
int df::Sprite::draw(int frame_number, Vector position) const
{
	if (frame_number < 0 || frame_number >= frame_count) {
		LM.writeLog("Sprite::draw() frame_number is not within bounds: frame_num=%d\n", frame_number);
		return -1;
	}
	return frame[frame_number].draw(position, color, transparency);
}

//Sets transparency character
void df::Sprite::setTransparency(char newTrans)
{
	transparency = newTrans;
}

//Gets transparency character
char df::Sprite::getTransparency()
{
	return transparency;
}
