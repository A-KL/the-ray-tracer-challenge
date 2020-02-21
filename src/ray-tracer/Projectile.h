#pragma once

#include "Vector3D.h"
#include "Point3D.h"

class Environment
{
public:
	Environment(const Vector3D& gravity, const Vector3D& wind)
		: Gravity(gravity), Wind(wind)
	{ }

	
	Vector3D Gravity;

	Vector3D Wind;
};

class Projectile
{
public:
	Projectile(const Point3D&  position, const Vector3D& velocity)
		: _position(position), _velocity(velocity)
	{ }

	Projectile Tick(const Environment&);

private:
	Vector3D _velocity;

	Point3D _position;
};