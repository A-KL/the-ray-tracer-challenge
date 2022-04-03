#include <math.h>
#include "Mathf.h"
#include "Color3D.h"
#include "Material3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Shape3D.h"

Shape3D::Shape3D(const Material3D& material) :
	Shape3D(Point3D::Origin, Matrix4d::Identity(), material)
{}

Shape3D::Shape3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{}

Shape3D::Shape3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Object3D(position, transform),
	Material(material)
{ }

bool Shape3D::operator==(const Shape3D& other) const
{
	return ((Object3D)*this) == other && Material == other.Material;
}

const Vector3D Shape3D::NormalAt(const Point3D& point) const
{
	auto inverse = Transformation.Inverse();
	auto local_point = inverse * point;
	auto local_normal = LocalNormalAt(local_point);
	auto world_normal = inverse.Transpose() * local_normal;
	world_normal.SetW(0);

	return world_normal.Normalize();
}