#pragma once

#include <math.h>
#include <iostream>

#include "Mathf.h"
#include "Primitive3D.h"

using namespace std;

class Vector3D :
	public Primitive3D<double>
{
public:
	Vector3D(const Vector3D& point)
		: Vector3D(point.X(), point.Y(), point.Z())
	{ }

	Vector3D(double x, double y, double z)
		: Vector3D(x, y, z, 0)
	{ }

	~Vector3D() 
	{}

	float Magniture();

	Vector3D Normalize();

	float Dot(const Vector3D&);

	Vector3D Cross(const Vector3D&);

	Vector3D operator+(const Vector3D&);

	Vector3D operator-(const Vector3D&);

	Vector3D operator*(float);

	friend ostream& operator<<(ostream& out, const Vector3D& p);

protected:
	Vector3D(double x, double y, double z, double w)
		: Primitive3D(x, y, z, w)
	{ }
};

