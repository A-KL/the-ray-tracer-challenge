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