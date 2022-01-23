#pragma once

#include <iostream>

#include "Mathf.h"
#include "Vector3D.h"
#include "Primitive3D.h"

using namespace std;

class Point3D :
	public Primitive3D<double>
{
public:
	Point3D(double x, double y, double z)
		: Primitive3D<double>(x, y, z, 0)
	{ }

	Point3D(const Point3D& point)
		: Point3D(point._x, point._y, point._z)
	{ }

	bool operator==(const Point3D& b);

	Vector3D operator-(const Point3D&);

	Point3D operator-(const Vector3D&);

	Point3D operator+(const Vector3D&);

	friend ostream& operator<<(ostream& out, const Point3D& p);
};

