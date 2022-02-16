#pragma once

#include "Shape3D.h"

class Sphere3D : 
	public Shape3D
{
	public:
		Sphere3D() :
			Sphere3D(Point3D::Origin, Matrix4d::Identity(), Material::Default, 1)
		{ }

		Sphere3D(Matrix4d& transform, double size = 1) :
			Sphere3D(Point3D::Origin, transform, Material::Default, size)
		{ }

		Sphere3D(const Material& material, double size = 1) :
			Sphere3D(Point3D::Origin, Matrix4d::Identity(), material, size)
		{ }

		Sphere3D(const Point3D& position, const Matrix4d& transform, const Material& material, double size) :
			Shape3D(position, transform, material),
			_size(size)
		{ }

		inline double R() const
		{
			return _size;
		}

		bool operator==(const Sphere3D& other) const
		{
			return (Shape3D)*this == other && _size == other._size;
		}	

	private:
		double _size;
};