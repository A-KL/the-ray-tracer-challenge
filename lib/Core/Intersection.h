#pragma once

#include "Shape3D.h"

class Intersection
{
public:
	Intersection(double t, const Shape3D& object);

	Intersection(double t, const Shape3D* object);

	const double Value;

	const Shape3D* Shape;

	bool operator==(const Intersection& other) const;

	bool operator!=(const Intersection& other) const;

	//bool operator>(const Intersection& other) const;

	//bool operator<(const Intersection& other) const;
};

struct IntersectionComparator
{
	bool operator ()(const Intersection& intersection1, const Intersection& intersection2)
	{
		if (intersection1.Value == intersection2.Value)
			return intersection1.Value < intersection2.Value;

		return intersection1.Value < intersection2.Value;
	}
};