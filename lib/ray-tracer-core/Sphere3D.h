#pragma once

#include <cassert>
#include<stdarg.h>
#include <initializer_list>

class Intersection
{
public:

private:
};

template<unsigned Size>
class Intersections
{
public:
	Intersections(std::initializer_list<Intersection> list)
	{
		assert(list.size() > 0);


		for (auto elem : list)
		{
			//std::cout << elem << std::endl;
		}
	}

	Intersections(int count, ...)
	{
		va_list ap;
		va_start(ap, count);

		for (int i = 0; i < count; i++) 
		{
			_intersections[i] = va_arg(ap, Intersection);
		}

		va_end(ap);
	}

private:
	Intersection _intersections[Size];
};

class Object3D
{
	public:
		Object3D(const Point3D& position) :
			_position(position),
			_transformation(matrix_identity_4d)
		{ }

		inline Point3D Location() const
		{
			return _position;
		}

		inline const Matrix4d Transformation() const
		{
			return _transformation;
		}

		inline void SetTransformation(const Matrix4d& transformation)
		{
			_transformation = transformation;
		}

	private:
		Point3D _position;
		Matrix4d _transformation;
};

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

		inline double R() const
		{
			return _size;
		}

	private:
		double _size;
		
};

