#pragma once

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

		bool virtual operator==(const Object3D& other) const
		{
			return 
				_position.X() == other._position.X() &&
				_position.Y() == other._position.Y() &&
				_position.Z() == other._position.Z() &&
				_transformation == other._transformation;
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