#include "Cone3D.hpp"

#include <math.h>
#include "Mathf.h"


Cone3D::Cone3D() :
    Cone3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Cone3D::Cone3D(const Matrix4d& transform) :
    Cone3D(Point3D::Origin, transform, Material3D::Default)
{ }

Cone3D::Cone3D(const Material3D& material) :
    Cone3D(Point3D::Origin, Matrix4d::Identity(), material)
{ }

Cone3D::Cone3D(const Matrix4d& transform, const Material3D& material) :
	Shape3D(Point3D::Origin, transform, material)
{ }

Cone3D::Cone3D(const Point3D& position, const Matrix4d& transform, const Material3D& material) :
	Shape3D(position, transform, material)
{ }

bool Cone3D::Cone3D::operator==(const Cone3D& other) const
{
	return *this == other;
}

const Vector3D Cone3D::LocalNormalAt(const Point3D& point) const
{
    auto dist = point.X() * point.X() + point.Z() * point.Z();

    if (dist < 1 && point.Y() >= Max - Mathf<double>::Epsilon()) {
        return Vector3D(0, 1, 0);
    }
    else if (dist < 1 && point.Y() <= Min + Mathf<double>::Epsilon()) {
        return Vector3D(0, -1, 0);
    }
    else {
      auto y = std::sqrt(point.X() * point.X() + point.Z() * point.Z());
      if (point.Y() > 0) {
          y = -y;
      }
      return Vector3D(point.X(), y, point.Z());
    }
}

bool Cone3D::CheckCap(const Ray3D& ray, const double t, double radius) const
{
    auto x = ray.Location.X() + t * ray.Direction.X();
    auto z = ray.Location.Z() + t * ray.Direction.Z();

    return (x * x + z * z) <= radius;
}

std::list<Intersection> Cone3D::LocalIntersect(const Ray3D& ray) const
{
    std::list<Intersection> results;

    auto a = ray.Direction.X() * ray.Direction.X() -  
             ray.Direction.Y() * ray.Direction.Y() + 
             ray.Direction.Z() * ray.Direction.Z();

    auto b = 2 * ray.Location.X() * ray.Direction.X() -
             2 * ray.Location.Y() * ray.Direction.Y() +
             2 * ray.Location.Z() * ray.Direction.Z();

    auto c = ray.Location.X() * ray.Location.X() -
             ray.Location.Y() * ray.Location.Y() + 
             ray.Location.Z() * ray.Location.Z();

    if (Mathf<double>::IsZero(a)) {

      if (!Mathf<double>::IsZero(b)) {

        auto t = -c / (2 * b);
        results.push_back(Intersection(t, this));
      }
      return results;
    }

    auto disc = b * b - (4.0 * a * c);

    disc  = Mathf<double>::ToZeroIfClose(disc);

    if (disc < 0) {
        return results;
    }

    auto t0 = (-b - std::sqrt(disc)) / (2 * a);
    auto t1 = (-b + std::sqrt(disc)) / (2 * a);

    if (t0 > t1) {
      Swap(t0, t1);
    }

    auto y0 = ray.Location.Y() + t0 * ray.Direction.Y();
    auto y1 = ray.Location.Y() + t1 * ray.Direction.Y();


    if (Min < y0 && y0 < Max) {
        results.push_back(Intersection(t0, this));
    }
    if (Min < y1 && y1 < Max) {
        results.push_back(Intersection(t1, this));
    }

    return results;
}

