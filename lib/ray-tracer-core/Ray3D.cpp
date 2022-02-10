#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Ray3D.h"

const Point3D Ray3D::Position(double value)
{
	return _position + _direction * value;
}

const Ray3D Ray3D::Transform(const Matrix4d& transformation) const
{
	auto pos = transformation * _position;

	auto dir = transformation * _direction;

	return Ray3D(pos, dir);
}