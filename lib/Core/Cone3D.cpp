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

bool Cone3D::operator==(const Cone3D& other) const
{
    return Shape3D::operator==(other) &&
        (Min == other.Min || Mathf<double>::Approximately(Min, other.Min)) &&
        (Max == other.Max || Mathf<double>::Approximately(Max, other.Max)) &&
        Closed == other.Closed;
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

bool Cone3D::CheckCap(const Ray3D& ray, const double t) const
{
    auto x = ray.Location.X() + t * ray.Direction.X();
    auto y = ray.Location.Y() + t * ray.Direction.Y();
    auto z = ray.Location.Z() + t * ray.Direction.Z();

    return (x * x + z * z) <= (y * y);
}

std::vector<Intersection> Cone3D::LocalIntersect(const Ray3D& ray) const
{
    std::vector<Intersection> results;

    IntersectCaps(ray, results);

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

void Cone3D::IntersectCaps(const Ray3D& ray, std::vector<Intersection>& results) const
{
    // a helper function to reduce duplication.
    // checks to see if the intersection at `t` is within a radius
    // of 1 (the radius of your cones) from the y axis.

    if (!Closed || Mathf<double>::IsZero(ray.Direction.Y())){
        return;
    }

    // check for an intersection with the lower end cap by intersecting
    // the ray with the plane at y=cone.minimum

    auto t = (Min - ray.Location.Y()) / ray.Direction.Y();
    if (CheckCap(ray, t)) {
        results.push_back(Intersection(t, this));
    }

    // check for an intersection with the upper end cap by intersecting
    // the ray with the plane at y=cone.maximum
    
    t = (Max - ray.Location.Y()) / ray.Direction.Y();
    if (CheckCap(ray, t)) {
        results.push_back(Intersection(t, this));
    }
}