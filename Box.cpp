#include "Box.h"

// Create box with (0,0) for the corner, and 0 for horiz and vert.
df::Box::Box()
{
	corner = Vector();
	horizontal = 0;
	vertical = 0;
}

// Create box with an upper-left corner, horiz and vert sizes.
df::Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
{
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

// Get upper left corner of box.
df::Vector df::Box::getCorner() const
{
	return corner;
}

// Set upper left corner of box.
void df::Box::setCorner(Vector new_corner)
{
	corner = new_corner;
}

// Get horizontal size of box.
float df::Box::getHorizontal() const
{
	return horizontal;
}

// Set horizontal size of box.
void df::Box::setHorizontal(float new_horizontal)
{
	horizontal = new_horizontal;
}

// Get vertical size of box.
float df::Box::getVertical() const
{
	return vertical;
}

// Set vertical size of box.
void df::Box::setVertical(float new_vertical)
{
	vertical = new_vertical;
}
