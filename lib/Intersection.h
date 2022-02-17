#pragma once

class Intersection
{
public:
	Intersection(double t, const Shape3D& object)
		: Value(t), Shape(&object)
	{ }

	Intersection(double t, const Shape3D* object)
		: Value(t), Shape(object)
	{ }

	const double Value;

	const Shape3D* Shape;

	bool operator==(const Intersection& other) const;

	bool operator!=(const Intersection& other) const;

	bool operator>(const Intersection& other) const;

	bool operator<(const Intersection& other) const;

	Intersection& operator =(const Intersection& other);
};
