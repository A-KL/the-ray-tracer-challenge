#pragma once

#include "Vector3D.h"
#include "Point3D.h"

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction)
		: _position(position), _direction(direction)
	{ }

private:
	Vector3D _direction;
	Point3D _position;
};
