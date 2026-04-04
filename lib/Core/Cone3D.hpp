
#pragma once

#include <list>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.hpp"

class Cone3D
	: virtual public Shape3D
{
public:
	Cone3D();

	Cone3D(const Matrix4d& transform);

	Cone3D(const Material3D& material);

	Cone3D(const Matrix4d& transform, const Material3D& material);

	Cone3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	double Min = - INFINITY;

	double Max = INFINITY;

	bool Closed = false;

	bool operator==(const Cone3D& other) const;

	std::list<Intersection> LocalIntersect(const Ray3D& ray) const;

	const Vector3D LocalNormalAt(const Point3D& point) const;

private:
	bool CheckCap(const Ray3D& ray, const double t, double radius) const;

	//void IntersectCaps(const Ray3D& ray, std::list<Intersection>& results) const;
};