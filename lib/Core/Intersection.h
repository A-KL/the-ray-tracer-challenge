#pragma once

class Shape3D;

class Intersection
{
public:
	Intersection(double t, const Shape3D& object);

	Intersection(double t, const Shape3D* object);

	Intersection(double t, const Shape3D& object, double u, double v);

	Intersection(double t, const Shape3D* object, double u, double v);

	const double Value;

	const Shape3D* Shape;

	const double U; // Used for smooth triangles

	const double V; // Used for smooth triangles

	bool operator==(const Intersection& other) const;

	bool operator!=(const Intersection& other) const;

	bool operator>(const Intersection& other) const;

	bool operator<(const Intersection& other) const;
};

// struct IntersectionComparator
// {
// 	inline bool operator ()(const Intersection& intersection1, const Intersection& intersection2)
// 	{
// 		if (intersection1.Value == intersection2.Value)
// 			return intersection1.Value < intersection2.Value;

// 		return intersection1.Value < intersection2.Value;
// 	}
// };