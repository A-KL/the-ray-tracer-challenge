#pragma once

#include <vector>

#include "Point3D.h"
#include "Vector3D.h"
#include "MatrixOps.h"
#include "Shape3D.h"
#include "Intersection.h"

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction);

	const Point3D Location;

	const Vector3D Direction;

	Point3D Position(double value) const;

	Ray3D Transform(const Matrix4d& transformation) const;

	std::vector<Intersection> Intersect(const std::vector<Shape3D*>& objects) const;
};
