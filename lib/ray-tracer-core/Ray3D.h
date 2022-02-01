#pragma once

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction)
		: _position(position), _direction(direction)
	{ }

	const Point3D Position(double value);

private:
	Vector3D _direction;
	Point3D _position;
};
