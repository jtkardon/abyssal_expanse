#pragma once
#include "Vector.h"
namespace df {
	class Box {

	private:
		Vector corner;       // Upper left corner of box.
		float horizontal;    // Horizontal dimension.
		float vertical;      // Vertical dimension.

	public:
		// Create box with (0,0) for the corner, and 0 for horiz and vert.
		Box();

		// Create box with an upper-left corner, horiz and vert sizes.
		Box(Vector init_corner, float init_horizontal, float init_vertical);

		// Get upper left corner of box.
		Vector getCorner() const;

		// Set upper left corner of box.
		void setCorner(Vector new_corner);

		// Get horizontal size of box.
		float getHorizontal() const;

		// Set horizontal size of box.
		void setHorizontal(float new_horizontal);

		// Get vertical size of box.
		float getVertical() const;

		// Set vertical size of box.
		void setVertical(float new_vertical);
	};
}