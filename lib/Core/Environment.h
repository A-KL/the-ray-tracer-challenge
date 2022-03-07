#pragma once

class Environment
{
public:
	Environment(const Vector3D& gravity, const Vector3D& wind)
		: Gravity(gravity), Wind(wind)
	{ }


	Vector3D Gravity;

	Vector3D Wind;
};