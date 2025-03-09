#include "Cube3D.hpp"

#include <math.h>
#include "Mathf.h"

Cube3D::Cube3D() :
    Cube3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Cube3D::Cube3D(const Matrix4d& transform) :
    Cube3D(Point3D::Origin, transform, Material3D::Default)
{ }

Cube3D::Cube3D(const Material3D& material) :
    Cube3D(Point3D::Origin, Matrix4d::Identity(), material)
{ }

Cube3D::Cube3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{ }

Cube3D::Cube3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Shape3D(position, transform, material)
{ }

bool Cube3D::Cube3D::operator==(const Cube3D& other) const
{
	return (Cube3D)*this == other;
}

const Vector3D Cube3D::LocalNormalAt(const Point3D& point) const
{
    auto abx_x = abs(point.X());
    auto abx_y = abs(point.Y());
    auto abx_z = abs(point.Z());

    auto maxc = Mathf<double>::Max(abx_x, abx_y, abx_z);

    if (maxc == abx_x)
    {
        return Vector3D(point.X(), 0, 0);
    }
    if (maxc == abx_y)
    {
        return Vector3D(0, point.Y(), 0);
    }

	return Vector3D(0, 0, point.Z());
}

std::list<Intersection> Cube3D::LocalIntersect(const Ray3D& ray) const
{
    double max_x = 0;
    double min_x = 0;

    double max_y = 0;
    double min_y = 0;

    double max_z = 0;
    double min_z = 0;

    CheckAxis(ray.Location.X(), ray.Direction.X(), min_x, max_x);
    CheckAxis(ray.Location.Y(), ray.Direction.Y(), min_y, max_y);
    CheckAxis(ray.Location.Z(), ray.Direction.Z(), min_z, max_z);

    auto tmin = Mathf<double>::Max(min_x, min_y, min_z);
    auto tmax = Mathf<double>::Min(max_x, max_y, max_z);

    std::list<Intersection> results;

    if (tmin <= tmax)
    {
        results.push_back(Intersection(tmin, this));
        results.push_back(Intersection(tmax, this));  
    }

    return results;

    //return std::list<Intersection> { Intersection(tmin, this), Intersection(tmax, this) };
}

void Cube3D::CheckAxis(const double origin, const double direction, double &tmin, double &tmax, double min, double max) const
{
	auto tmin_numerator = (min - origin);
	auto tmax_numerator = (max - origin);

	if (abs(direction) >= Mathf<double>::Epsilon()) {
		tmin = tmin_numerator / direction;
		tmax = tmax_numerator / direction;
	} else {
		tmin = tmin_numerator * INFINITY;
		tmax = tmax_numerator * INFINITY;
	}

	if (tmin > tmax) {
		auto tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}
}