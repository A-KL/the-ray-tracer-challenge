#include <math.h>

#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Material3D.h"
#include "Shape3D.h"
#include "Intersection.h"

#include "Ray3D.h"

#include "RayTracer.h"

Ray3D::Ray3D(const Point3D& position, const Vector3D& direction)
	: Location(position), Direction(direction)
{ }

Point3D Ray3D::Position(double value) const
{
	return Location + Direction * value;
}

Ray3D Ray3D::Transform(const Matrix4d& transformation) const
{
	auto pos = transformation * Location;

	auto dir = transformation * Direction;

	return Ray3D(pos, dir);
}

std::list<Intersection> Ray3D::Intersect(const std::list<Shape3D*>& objects) const
{
	std::list<Intersection> result;

	for (auto const& object : objects)
	{
		auto intersections = ray_intersect(object, *this);

		for (auto const& intersection : intersections)
		{
			result.push_back(intersection);
		}
	}

	result.sort(IntersectionComparator());

	return result;
}