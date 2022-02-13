#pragma once

#include <math.h>
#include <iostream>

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

	double Magniture();

	Vector3D Normalize();

	double Dot(const Vector3D&) const;

	static double Dot(const Vector3D& v1, const Vector3D& v2);

	static Vector3D Reflect(const Vector3D& v1, const Vector3D& v2);

	Vector3D Cross(const Vector3D&) const;

	Vector3D operator+(const Vector3D&) const;

	Vector3D operator-(const Vector3D&) const;

	Vector3D operator*(double) const;

	friend ostream& operator<<(ostream& out, const Vector3D& p);

protected:
	Vector3D(double x, double y, double z, double w)
		: Primitive3D(x, y, z, w)
	{ }
};

