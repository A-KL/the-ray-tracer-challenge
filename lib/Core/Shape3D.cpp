#include <math.h>
#include "Mathf.h"
#include "Color3D.h"
#include "Material.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Shape3D.h"

bool Shape3D::operator==(const Shape3D& other) const
{
	return ((Object3D)*this) == other && Mat == other.Mat;
}

const Vector3D Shape3D::NormalAt(const Point3D& point) const
{
	auto inverse = Transformation.Inverse();
	auto object_point = inverse * point;
	auto object_normal = object_point - Position;
	auto world_normal = inverse.Transpose() * object_normal;
	world_normal.SetW(0);

	return world_normal.Normalize();
}