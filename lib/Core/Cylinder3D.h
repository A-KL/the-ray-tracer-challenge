#pragma once

#include <vector>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.h"

class Cylinder3D
	: virtual public Shape3D
{
public:
	Cylinder3D();

	Cylinder3D(const Matrix4d transform);

	Cylinder3D(const Material3D material);

	Cylinder3D(const Matrix4d transform, const Material3D material);

	Cylinder3D(const Point3D position, const Matrix4d transform, const Material3D material);

	double Min = - INFINITY;

	double Max = INFINITY;

	bool Closed = false;

	bool operator==(const Cylinder3D& other) const;

	std::vector<Intersection> LocalIntersect(const Ray3D& ray) const;

	const Vector3D LocalNormalAt(const Point3D& point, const Intersection* hit = nullptr) const;

private:
	bool CheckCap(const Ray3D& ray, const double t) const;

	void IntersectCaps(const Ray3D& ray, std::vector<Intersection>& results) const;
};