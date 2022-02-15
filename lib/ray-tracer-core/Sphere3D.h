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

		Sphere3D(Matrix4d& translate, double size = 1) :
			Object3D(Point3D::Origin),
			_material(Material::Default),
			_size(size)
		{ }


		Sphere3D(const Point3D& position, const Matrix4d& translate, const Material& material, double size = 1) :
			Object3D(position, translate),
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