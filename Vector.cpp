#include "Vector.h"
#include "Math.h"
#include "LogManager.h"

using namespace df;
// Create Vector with (x,y).
Vector::Vector(float init_x, float init_y)
{
	x = init_x;
	y = init_y;
}

// Default 2d (x,y) is (0,0).
Vector::Vector()
{
	x = 0;
	y = 0;
}

// Get/set horizontal component.
void Vector::setX(float new_x)
{
	x = new_x;
}


float Vector::getX() const
{
	return x;
}

// Get/set vertical components
void Vector::setY(float new_y)
{
	y = new_y;
}

float Vector::getY() const
{
	return y;
}

// Set horizontal & vertical components.
void Vector::setXY(float new_x, float new_y)
{
	x = new_x;
	y = new_y;
}

// Return magnitude of vector.
float Vector::getMagnitude() const
{
	return sqrt(x * x + y * y);
}

// Normalize vector.
void Vector::normalize()
{
	float length = getMagnitude();
	if (length > 0) {
		x /= length;
		y /= length;
	}
}

// Scale vector.
void Vector::scale(float s)
{
	x *= s;
	y *= s;
}

// Add two Vectors, return new Vector.
Vector Vector::operator+(const Vector& other) const
{
	Vector v;
	v.x = x + other.x;
	v.y = y + other.y;
	return v;
}

// Checks if two Vectors are equal
bool Vector::operator==(const Vector& other) const
{
	return (x == other.x) && (y == other.y);
}

// Checks if two Vectors are not equal
bool Vector::operator!=(const Vector& other) const
{
	return (x != other.x) || (y != other.y);
}
