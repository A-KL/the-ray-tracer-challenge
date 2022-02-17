#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Object3D.h"

bool Object3D::operator==(const Object3D& other) const
{
	// TODO: fix this
	return
		Position.X() == other.Position.X() &&
		Position.Y() == other.Position.Y() &&
		Position.Z() == other.Position.Z() &&
		Transformation == other.Transformation;
}

const Vector3D Object3D::NormalAt(const Point3D& point) const
{
	auto inverse = Transformation.Inverse();
	auto object_point = inverse * point;
	auto object_normal = object_point - Position;
	auto world_normal = inverse.Transpose() * object_normal;
	world_normal.SetW(0);

	return world_normal.Normalize();
}