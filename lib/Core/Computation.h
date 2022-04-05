#pragma once

#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material3D.h"
#include "Shape3D.h"

#include "Intersection.h"
#include "Ray3D.h"

struct Computation
{
	const static Computation Prepare(const Intersection& intersection, const Ray3D& ray);

	const Intersection Intersect;

	const Point3D Position;

	const Point3D OverPosition;

	const Vector3D Normal;

	const Vector3D Camera;

	const bool IsInside;
};