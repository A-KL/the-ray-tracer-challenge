#include "Intersection.h"

Intersection::Intersection(double t, const Shape3D& object)
	: Value(t), Shape(&object), U(0), V(0)
{ }

Intersection::Intersection(double t, const Shape3D* object)
	: Value(t), Shape(object), U(0), V(0)
{ }

Intersection::Intersection(double t, const Shape3D& object, double u, double v)
	: Value(t), Shape(&object), U(u), V(v)
{ }

Intersection::Intersection(double t, const Shape3D* object, double u, double v)
	: Value(t), Shape(object), U(u), V(v)
{ }

bool Intersection::operator==(const Intersection& other) const
{
	return Value == other.Value && Shape == other.Shape && U == other.U && V == other.V;
}

bool Intersection::operator!=(const Intersection& other) const
{
	return !(*this == other);
}

bool Intersection::operator>(const Intersection& other) const
{
	return Value > other.Value;
}

bool Intersection::operator<(const Intersection& other) const
{
	return Value < other.Value;
}