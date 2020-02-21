#pragma once

#include <iostream>

#include "Primitive3D.h"

using namespace std;

class Vector3D :
	public Primitive3D
{
public:
	Vector3D(float x, float y, float z)
		: Vector3D(x, y, z, 1)
	{ }

	Vector3D(const Vector3D& point)
		: Vector3D(point._x, point._y, point._z)
	{ }

	float Magniture();

	Vector3D Normalize();

	float Dot(const Vector3D&);

	Vector3D Cross(const Vector3D&);

	bool operator==(const Vector3D&);

	Vector3D operator+(const Vector3D&);

	Vector3D operator-(const Vector3D&);

	Vector3D operator*(float);

	friend ostream& operator << (ostream& out, const Vector3D& p);

protected:
	Vector3D(float x, float y, float z, float w)
		: Primitive3D(x, y, z, w)
	{ }
};

