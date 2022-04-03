#include <math.h>
#include "Mathf.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Object3D.h"

Object3D::Object3D(const Point3D& position) :
	Object3D(position, matrix_identity_4d)
{ }

Object3D::Object3D(const Point3D& position, const Matrix4d& transform) :
	Position(position),
	Transformation(transform)
{ }

bool Object3D::operator==(const Object3D& other) const
{
	return
		Position == other.Position &&
		Transformation == other.Transformation;
}