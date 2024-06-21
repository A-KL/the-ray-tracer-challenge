#include "Sphere3D.h"

Sphere3D::Sphere3D() :
	Sphere3D(Point3D::Origin, Matrix4d::Identity(), Material3D::Default)
{ }

Sphere3D::Sphere3D(const Matrix4d& transform) :
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

std::list<Intersection> Sphere3D::LocalIntersect(const Ray3D& ray) const
{
	Vector3D object_to_ray = ray.Location - Position;
	
	double a = Vector3D::Dot(ray.Direction, ray.Direction);
	
	double b = 2.0 * Vector3D::Dot(ray.Direction, object_to_ray);
	
	double c = Vector3D::Dot(object_to_ray, object_to_ray) - 1.0;
	
	double d = b * b - 4.0 * a * c;
	
	std::list<Intersection> result;
	
	if (d >= 0)
	{
		double sd = sqrt(d);
		double aa = 2.0 * a;
		double t1 = (-b - sd) / aa;
		double t2 = (-b + sd) / aa;
	
		result.push_back(Intersection(t1, this));
		result.push_back(Intersection(t2, this));
		result.sort(IntersectionComparator());
	}
	
	return result;
}
