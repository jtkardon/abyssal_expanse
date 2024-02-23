#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace df {

	class Vector {

	private:
		float x;   // Horizontal coordinate in 2d world.
		float y;   // Vertical coordinate in 2d world.

	public:
		// Create Vector with (x,y).
		Vector(float init_x, float init_y);

		// Default 2d (x,y) is (0,0).
		Vector();

		// Get/set horizontal component.
		void setX(float new_x);
		float getX() const;

		// Get/set vertical component.
		void setY(float new_y);
		float getY() const;

		// Set horizontal & vertical components.
		void setXY(float new_x, float new_y);

		// Return magnitude of vector.
		float getMagnitude() const;

		// Normalize vector.
		void normalize();

		// Scale vector.
		void scale(float s);

		// Add two Vectors, return new Vector.
		Vector operator+(const Vector& other) const;

		// Checks if two Vectors are equal
		bool operator==(const Vector& other) const;

		// Checks if two Vectors are not equal
		bool operator!=(const Vector& other) const;
	};
}
#endif