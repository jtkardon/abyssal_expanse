#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventView.h"

using namespace std;
// Construct ViewObject.
// Object settings: SPECTRAL, max alt.
// ViewObject defaults: border, top_center, default color.
df::ViewObject::ViewObject()
{
	//Initialize Object attributes
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");

	//Initialize ViewObject attributes
	setValue(0);
	setBorder(true);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);
	setViewString("");

}

// Draw view string and value.
int df::ViewObject::draw()
{
	setLocation(location);
	string temp_str;
	//Display view string + value
	if (border)
		temp_str = "| " + getViewString() + " " + to_string(value) + " |";
	else
		temp_str = getViewString() + " " + to_string(value);


	//Draw centered at position
	Vector pos = DM.viewToWorld(getPosition());
	DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

	if (border) {
		//Draw box
		string topAndBottom = "*";
		for (int i = 0; i < temp_str.length() - 2; i++)
			topAndBottom += "-";
		topAndBottom += "*";
		Vector topPos = Vector(pos.getX(), pos.getY() - 1);
		Vector botPos = Vector(pos.getX(), pos.getY() + 1);
		DM.drawString(topPos, topAndBottom, CENTER_JUSTIFIED, getColor());
		DM.drawString(botPos, topAndBottom, CENTER_JUSTIFIED, getColor());
	}

	return 0;
}

// Handle `view' event if tag matches view_string (others ignored).
// Return 0 if ignored, else 1 if handled.
int df::ViewObject::eventHandler(const Event* p_e)
{
	//See if this is a 'view' event
	if (p_e->getType() == VIEW_EVENT) {
		const EventView* p_ve = static_cast <const EventView*> (p_e);
		
		//See if this event is meant for this object
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta())
				setValue(getValue() + p_ve->getValue()); //change in value
			else
				setValue(p_ve->getValue());
		}	
		return 1;
	}
	return 0;
}

// General location of ViewObject on screen.
void df::ViewObject::setLocation(ViewObjectLocation new_location)
{
	Vector p = Vector();
	float delta = 0;
	//Set new position based on location
	switch (new_location)
	{
	case df::TOP_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
		if (!getBorder())
			delta = -1;
		break;
	case df::TOP_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
		if (!getBorder())
			delta = -1;
		break;
	case df::TOP_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
		if (!getBorder())
			delta = -1;
		break;
	case df::CENTER_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6,
			WM.getView().getVertical() / 2);
		break;
	case df::CENTER_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6,
			WM.getView().getVertical() / 2);
		break;
	case df::CENTER_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6,
			WM.getView().getVertical() / 2);
		break;
	case df::BOTTOM_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			delta = 1;
		break;
	case df::BOTTOM_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			delta = 1;
		break;
	default: // df::BOTTOM_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			delta = 1;
		break;
	}
	//Shift as needed, based on border
	p.setY(p.getY() + delta);

	//Set position of object to new position
	setPosition(p);

	//Set new location
	location = new_location;
}

// Set view value.
void df::ViewObject::setValue(int new_value)
{
	value = new_value;
}

// Get view value.
int df::ViewObject::getValue() const
{
	return value;
}

// Set view border (true = display border).
void df::ViewObject::setBorder(bool new_border)
{
	if (border != new_border)
		border = new_border;
	//Reset location to account for border setting
	setLocation(location);
}

// Get view border (true = display border).
bool df::ViewObject::getBorder()
{
	return border;
}

// Set view color.
void df::ViewObject::setColor(Color new_color)
{
	color = new_color;
}

// Get view color.
df::Color df::ViewObject::getColor() const
{
	return color;
}

// Set view display string.
void df::ViewObject::setViewString(std::string new_view_string)
{
	view_string = new_view_string;
}

// Get view display string.
std::string df::ViewObject::getViewString() const
{
	return view_string;
}
