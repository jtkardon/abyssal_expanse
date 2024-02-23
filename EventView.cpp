#include "EventView.h"

// Create view event with tag VIEW_EVENT, value 0 and delta false.
df::EventView::EventView()
{
	tag = "";
	value = 0;
	delta = false;
	setType(VIEW_EVENT);
}

// Create view event with tag, value and delta as indicated.
df::EventView::EventView(std::string new_tag, int new_value, bool new_delta)
{
	tag = new_tag;
	value = new_value;
	delta = new_delta;
	setType(VIEW_EVENT);
}

// Set tag to new tag.
void df::EventView::setTag(std::string new_tag)
{
	tag = new_tag;
}

// Get tag.
std::string df::EventView::getTag() const
{
	return tag;
}

// Set value to new value.
void df::EventView::setValue(int new_value)
{
	value = new_value;
}

// Get value.
int df::EventView::getValue() const
{
	return value;
}

// Set delta to new delta.
void df::EventView::setDelta(bool new_delta)
{
	delta = new_delta;
}

// Get delta.
bool df::EventView::getDelta() const
{
	return delta;
}
