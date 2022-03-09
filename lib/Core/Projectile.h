#pragma once

class Projectile
{
public:
	Projectile(const Point3D& position, const Vector3D& velocity)
		: _position(position), _velocity(velocity)
	{ }

	Projectile Tick(const Environment&) const;

	inline Point3D Position()
	{
		return _position;
	}

private:
	Point3D _position;
	Vector3D _velocity;	
};