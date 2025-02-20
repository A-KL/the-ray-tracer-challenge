#pragma once

#include "Vector3D.h"
#include "Point3D.h"

#include "Intersection.h"
#include "Ray3D.h"

struct Computation
{
	const static Computation Prepare(const Intersection& intersection, const Ray3D& ray);

	const static Computation Prepare(const Intersection& intersection, const Ray3D& ray, const std::vector<const Intersection>& intersections);

	const double SchlickValue() const;

	const Intersection Intersect;

	const Point3D Position;

	const Point3D OverPosition;

	const Point3D UnderPosition;

	const Vector3D Normal;

	const Vector3D Camera;

	const Vector3D Reflection;

	const bool IsInside;

	const double N1;

	const double N2;
};