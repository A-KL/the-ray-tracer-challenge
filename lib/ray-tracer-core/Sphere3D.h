#pragma once

#include "Object3D.h"

class Sphere3D : 
	public Object3D
{
	public:
		Sphere3D() :
			Sphere3D(Point3D(0,0,0), 1)
		{ }

		Sphere3D(const Point3D& position, double size) :
			Object3D(position),
			_size(size)	
		{ }


		Sphere3D(const Matrix4d& translate, double size = 1) :
			Object3D(Point3D(0, 0, 0), translate),
			_size(size)
		{ }

		inline double R() const
		{
			return _size;
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
		
};