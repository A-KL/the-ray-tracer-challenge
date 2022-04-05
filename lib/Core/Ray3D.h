#pragma once

#include <list>

#include "MatrixOps.hpp"

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction);

	const Point3D Location;

	const Vector3D Direction;

	Point3D Position(double value) const;

	Ray3D Transform(const Matrix4d& transformation) const;

	std::list<Intersection> Intersect(const std::list<Shape3D*>& objects) const;
};
