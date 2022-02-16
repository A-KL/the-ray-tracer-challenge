#include <list>

#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Shape3D.h"

#include "Ray3D.h"
#include "Intersection.h"
#include "RayTracer.h"

struct IntersectionComparator
{
	bool operator ()(const Intersection& intersection1, const Intersection& intersection2)
	{
		if (intersection1.T() == intersection2.T())
			return intersection1.T() < intersection2.T();

		return intersection1.T() < intersection2.T();
	}
};

std::list<Intersection> ray_intersect(const Shape3D& object, const Ray3D& ray)
{
	Ray3D final_ray = ray.Transform(object.Transformation().Inverse());

	Vector3D object_to_ray = final_ray.Location() - object.Position();

	float a = Vector3D::Dot(final_ray.Direction(), final_ray.Direction());

	float b = 2 * Vector3D::Dot(final_ray.Direction(), object_to_ray);

	float c = Vector3D::Dot(object_to_ray, object_to_ray) - 1;

	float d = pow(b, 2) - 4 * a * c;

	std::list<Intersection> result;

	if (d >= 0)
	{
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);

		result = {
			Intersection(t1, object),
			Intersection(t2, object)
		};
	}

	return result;
}

Intersection ray_hit(const std::list<Intersection>& intersections)
{
	std::list<Intersection> soreted(intersections);

	soreted.sort(IntersectionComparator());

	for (auto& intersection : soreted)
	{
		if (intersection.T() >= 0)
		{
			return intersection;
		}
	}

	return Intersection::Empty;
}