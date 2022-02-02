#pragma once

class Sphere3D 
{
	public:
		Sphere3D() :
			Sphere3D(Point3D(0,0,0), 1)
		{ }

		Sphere3D(const Point3D& position, double size) :
			_position(position), 
			_size(size)
		{ }

		inline double R() const
		{
			return _size;
		}

	private:
		double _size;
		Point3D _position;
};

