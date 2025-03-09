#pragma once

#include <list>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.hpp"

class Cylinder3D
	: virtual public Shape3D
{
public:
    Cylinder3D();

    Cylinder3D(const Matrix4d& transform);

	Cylinder3D(const Material3D& material);

	Cylinder3D(const Matrix4d& transform, const Material3D& material);

	Cylinder3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	bool operator==(const Cylinder3D& other) const;

	std::list<Intersection> LocalIntersect(const Ray3D& ray) const;

	const Vector3D LocalNormalAt(const Point3D& point) const;
};