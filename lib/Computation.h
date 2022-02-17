#pragma once

struct Computation
{
	const static Computation Prepare(const Intersection& intersection, const Ray3D& ray);

	const Intersection Intersect;

	const Point3D Position;

	const Vector3D Normal;

	const Vector3D Camera;

	const bool IsInside;
};