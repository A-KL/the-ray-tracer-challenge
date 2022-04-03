#include <list>
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

//std::list<Intersection> Shape3D::Intersect(const Ray3D& ray) const
//{
//	Ray3D final_ray = ray.Transform(Transformation.Inverse());
//
//	Vector3D object_to_ray = final_ray.Location - Position;
//
//	double a = Vector3D::Dot(final_ray.Direction, final_ray.Direction);
//
//	double b = 2.0 * Vector3D::Dot(final_ray.Direction, object_to_ray);
//
//	double c = Vector3D::Dot(object_to_ray, object_to_ray) - 1.0;
//
//	double d = b * b - 4.0 * a * c;
//
//	std::list<Intersection> result;
//
//	if (d >= 0)
//	{
//		double sd = sqrt(d);
//		double aa = 2.0 * a;
//		double t1 = (-b - sd) / aa;
//		double t2 = (-b + sd) / aa;
//
//		result.push_back(Intersection(t1, object));
//		result.push_back(Intersection(t2, object));
//		result.sort(IntersectionComparator());
//	}
//
//	return result;
//}