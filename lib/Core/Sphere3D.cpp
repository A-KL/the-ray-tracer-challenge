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
#include "Sphere3D.h"

#include "Intersection.h"

Sphere3D::Sphere3D() :
	Sphere3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Sphere3D::Sphere3D(Matrix4d& transform) :
	Sphere3D(Point3D::Origin, transform, Material3D::Default)
{ }

Sphere3D::Sphere3D(const Material3D& material) :
	Sphere3D(Point3D::Origin, Matrix4d::Identity(), material)
{ }

Sphere3D::Sphere3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{ }

Sphere3D::Sphere3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Shape3D(position, transform, material)
{ }

bool Sphere3D::Sphere3D::operator==(const Sphere3D& other) const
{
	return (Sphere3D)*this == other;
}

const Vector3D Sphere3D::LocalNormalAt(const Point3D& point) const
{
	auto object_normal = point - Position;

	return object_normal;
}
