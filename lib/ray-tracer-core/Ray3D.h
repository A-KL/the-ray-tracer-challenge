#pragma once

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction)
		: _position(position), _direction(direction)
	{ }

	const Point3D Position(double value);

	inline Point3D Location() const
	{
		return _position;
	}

	inline Vector3D Direction() const
	{
		return _direction;
	}

private:
	Vector3D _direction;
	Point3D _position;
};
