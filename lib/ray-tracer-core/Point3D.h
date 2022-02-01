#pragma once

#include <iostream>

using namespace std;

class Point3D :
	public Primitive3D<double>
{
public:
	Point3D()
		: Point3D(0, 0, 0)
	{ }

	Point3D(const Point3D& point)
		: Point3D(point.X(), point.Y(), point.Z())
	{ }

	Point3D(double x, double y, double z)
		: Primitive3D<double>(x, y, z, 1)
	{ }

	Vector3D operator-(const Point3D&);

	Point3D operator-(const Vector3D&);

	Point3D operator+(const Vector3D&);

	friend ostream& operator<<(ostream& out, const Point3D& p);
};

