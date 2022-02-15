#pragma once
#include "Mathf.h"
#include "Color3D.h"
#include "Material.h"
#include "Object3D.h"

class Sphere3D : 
	public Object3D
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
			Object3D(position, transform),
			_material(material),
			_size(size)
		{ }

		inline double R() const
		{
			return _size;
		}

		inline Material GetMaterial() const
		{
			return _material;
		}

		bool operator==(const Object3D& other) const
		{
			return false;
		}

		bool operator==(const Sphere3D& other) const
		{
			return (Object3D)*this == (Object3D)other && _size == other._size;
		}	

	private:
		double _size;
		Material _material;	
};