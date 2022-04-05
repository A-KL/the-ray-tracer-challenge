#include "Intersection.h"

Intersection::Intersection(double t, const Shape3D& object)
	: Value(t), Shape(&object)
{ }

Intersection::Intersection(double t, const Shape3D* object)
	: Value(t), Shape(object)
{ }

bool Intersection::operator==(const Intersection& other) const
{
	return Value == other.Value && Shape == other.Shape;
}

bool Intersection::operator!=(const Intersection& other) const
{
	return !(*this == other);
}

//bool Intersection::operator>(const Intersection& other) const
//{
//	return Value > other.Value;
//}
//
//bool Intersection::operator<(const Intersection& other) const
//{
//	return Value < other.Value;
//}