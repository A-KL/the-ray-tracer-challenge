#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Shape3D.h"

#include "Ray3D.h"
#include "Intersection.h"
#include "Computation.h"

const Computation Computation::Prepare(const Intersection& intersection, const Ray3D& ray)
{
	auto position = ray.Position(intersection.Value);
	auto normal = intersection.Shape->NormalAt(position);
	auto camera = -ray.Direction;
	auto inside = Vector3D::Dot(normal, camera) < 0;

	return Computation{ intersection, position, inside ? -normal : normal, camera, inside };
}