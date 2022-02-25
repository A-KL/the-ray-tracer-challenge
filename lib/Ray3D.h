#pragma once

class Ray3D
{
public:
	Ray3D(const Point3D& position, const Vector3D& direction)
		: Location(position), Direction(direction)
	{ }

	const Point3D Location;

	const Vector3D Direction;

	Point3D Position(double value) const;

	Ray3D Transform(const Matrix4d& transformation) const;
};
