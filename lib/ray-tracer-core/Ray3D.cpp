#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Ray3D.h"

const Point3D Ray3D::Position(double value)
{
	return _position + _direction * value;
}