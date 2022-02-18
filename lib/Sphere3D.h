#pragma once

#include "Shape3D.h"

struct Sphere3D : virtual public Shape3D
{
	Sphere3D() :
		Sphere3D(Point3D::Origin, Matrix4d::Identity(), Material::Default)
	{ }

	Sphere3D(Matrix4d& transform) :
		Sphere3D(Point3D::Origin, transform, Material::Default)
	{ }

	Sphere3D(const Material& material) :
		Sphere3D(Point3D::Origin, Matrix4d::Identity(), material)
	{ }

	Sphere3D(const Point3D& position, const Matrix4d& transform, const Material& material) :
		Shape3D(position, transform, material)
	{ }

	//virtual const Vector3D NormalAt(const Point3D& point) const;

	bool operator==(const Sphere3D& other) const;
};