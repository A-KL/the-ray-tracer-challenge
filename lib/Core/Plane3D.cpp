#include <math.h>

#include "Mathf.h"

#include "Plane3D.hpp"

Plane3D::Plane3D() :
	Plane3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Plane3D::Plane3D(Matrix4d& transform) :
	Plane3D(Point3D::Origin, transform, Material3D::Default)
{ }

Plane3D::Plane3D(const Material3D& material) :
	Plane3D(Point3D::Origin, Matrix4d::Identity(), material)
{ }

Plane3D::Plane3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{ }

Plane3D::Plane3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Shape3D(position, transform, material)
{ }

bool Plane3D::Plane3D::operator==(const Plane3D& other) const
{
	return (Plane3D)*this == other;
}

const Vector3D Plane3D::LocalNormalAt(const Point3D& point) const
{
	return Vector3D(0, 1, 0);
}

std::list<Intersection> Plane3D::LocalIntersect(const Ray3D& ray) const
{
	std::list<Intersection> result;

	if (fabs(ray.Direction.Y()) < Mathf<double>::Epsilon())
	{
		return result;
	}

	auto t = -ray.Location.Y() / ray.Direction.Y();

	result.push_back(Intersection(t, this));

	return result;
}