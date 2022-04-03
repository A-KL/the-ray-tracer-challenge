#include <list>
#include <math.h>

#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material3D.h"
#include "Object3D.h"
#include "Shape3D.h"

#include "Intersection.h"
#include "Light3D.h"
#include "Ray3D.h"
#include "Computation.h"

#include "RayTracer.h"

const static std::list<Intersection> EmptyList;

//std::list<Intersection> ray_intersect(const std::list<Shape3D*>& objects, const Ray3D& ray)
//{
//	std::list<Intersection> result;
//
//	for (auto const& object : objects) 
//	{
//		auto intersections = ray_intersect(object, ray);
//
//		for (auto const& intersection : intersections)
//		{
//			result.push_back(intersection);
//		}
//	}
//
//	result.sort(IntersectionComparator());
//
//	return result;
//}

std::list<Intersection> ray_intersect(const Shape3D* object, const Ray3D& ray)
{
	Ray3D final_ray = ray.Transform(object->Transformation.Inverse());

	Vector3D object_to_ray = final_ray.Location - object->Position;

	double a = Vector3D::Dot(final_ray.Direction, final_ray.Direction);

	double b = 2.0 * Vector3D::Dot(final_ray.Direction, object_to_ray);

	double c = Vector3D::Dot(object_to_ray, object_to_ray) - 1.0;

	double d = b * b - 4.0 * a * c;

	std::list<Intersection> result;

	if (d >= 0)
	{
		double sd = sqrt(d);
		double aa = 2.0 * a;
		double t1 = (-b - sd) / aa;
		double t2 = (-b + sd) / aa;

		result.push_back(Intersection(t1, object));
		result.push_back(Intersection(t2, object));
		result.sort(IntersectionComparator());
	}

	return result;
}

std::list<Intersection> ray_hit(const std::list<Intersection>& intersections)
{
	std::list<Intersection> sorted(intersections);

	sorted.sort(IntersectionComparator());

	for (auto& intersection : sorted)
	{
		if (intersection.Value >= 0)
		{
			return std::list<Intersection> { intersection };
		}
	}

	return EmptyList;
}