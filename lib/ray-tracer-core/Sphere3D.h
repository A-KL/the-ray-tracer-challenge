#pragma once

class Object3D
{
	public:
		Object3D(const Point3D& position) :
			_position(position),
			_transformation(matrix_identity_4d)
		{ }

		Object3D(const Point3D& position, const Matrix4d& transform) :
			_position(position),
			_transformation(transform)
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

		Vector3D NormalAt(const Point3D& point) const
		{
			auto object_point = _transformation.Inverse() * point;
			auto object_normal = object_point - _position;
			auto world_normal = _transformation.Inverse().Transpose() * object_normal;
			//world_normal.W();

			return world_normal.Normalize();
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