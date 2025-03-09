#include "Cylinder3D.hpp"

#include <math.h>
#include "Mathf.h"

Cylinder3D::Cylinder3D() :
    Cylinder3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Cylinder3D::Cylinder3D(const Matrix4d& transform) :
    Cylinder3D(Point3D::Origin, transform, Material3D::Default)
{ }

Cylinder3D::Cylinder3D(const Material3D& material) :
    Cylinder3D(Point3D::Origin, Matrix4d::Identity(), material)
{ }

Cylinder3D::Cylinder3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{ }

Cylinder3D::Cylinder3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Shape3D(position, transform, material)
{ }

bool Cylinder3D::Cylinder3D::operator==(const Cylinder3D& other) const
{
	return (Cylinder3D)*this == other;
}

const Vector3D Cylinder3D::LocalNormalAt(const Point3D& point) const
{
	return Vector3D(point.X(), 0, point.Z());
}

std::list<Intersection> Cylinder3D::LocalIntersect(const Ray3D& ray) const
{
    std::list<Intersection> results;

    auto a = ray.Direction.X() * ray.Direction.X() + ray.Direction.Z() * ray.Direction.Z();

    if (Mathf<double>::IsZero(a))
    {
        return results;
    }

    auto b = 2 * ray.Location.X() * ray.Direction.X() +
             2 * ray.Location.Z() * ray.Direction.Z();

    auto c = ray.Location.X() * ray.Location.X() + ray.Location.Z() * ray.Location.Z() - 1;

    auto disc = b * b - 4 * a * c;

    if (disc < 0)
    {
        return results;
    }

    auto t0 = (-b - std::sqrt(disc)) / (2 * a);
    auto t1 = (-b + std::sqrt(disc)) / (2 * a);

    results.push_back(Intersection(t0, this));
    results.push_back(Intersection(t1, this));

    // std::cout << "t0: " << t0 << " t1: " << t1 << std::endl;

    return results;
}