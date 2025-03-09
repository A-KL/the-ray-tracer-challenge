#pragma once

#include <list>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.hpp"

class Cube3D
	: virtual public Shape3D
{
public:
    Cube3D();

    Cube3D(const Matrix4d& transform);

	Cube3D(const Material3D& material);

	Cube3D(const Matrix4d& transform, const Material3D& material);

	Cube3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	bool operator==(const Cube3D& other) const;

	std::list<Intersection> LocalIntersect(const Ray3D& ray) const;

	const Vector3D LocalNormalAt(const Point3D& point) const;

private:
	void CheckAxis(const double origin, const double direction, double &tmin, double &tmax, double min = -1, double max = 1) const;
};