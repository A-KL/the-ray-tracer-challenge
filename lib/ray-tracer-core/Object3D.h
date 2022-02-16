#pragma once

class Object3D
{
public:
	Object3D(const Point3D& position) :
		Object3D(position, matrix_identity_4d)
	{ }

	Object3D(const Point3D& position, const Matrix4d& transform) :
		_position(position),
		_transformation(transform)
	{ }

	inline Point3D Position() const
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
		// TODO: fix this
		return
			_position.X() == other._position.X() &&
			_position.Y() == other._position.Y() &&
			_position.Z() == other._position.Z() &&
			_transformation == other._transformation;
	}

	Vector3D NormalAt(Point3D& point) const
	{
		auto inverse = _transformation.Inverse();
		auto object_point = inverse * point;
		auto object_normal = object_point - _position;
		auto world_normal = inverse.Transpose() * object_normal;
		world_normal.SetW(0);

		return world_normal.Normalize();
	}

private:
	Point3D _position;
	Matrix4d _transformation;
};


