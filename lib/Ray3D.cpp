#include "Mathf.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Ray3D.h"

Point3D Ray3D::Position(double value) const
{
	return Location + Direction * value;
}

Ray3D Ray3D::Transform(const Matrix4d& transformation) const
{
	auto pos = transformation * Location;

	auto dir = transformation * Direction;

	return Ray3D(pos, dir);
}