#pragma once

#include <iostream>

#include "Primitive3D.h"

using namespace std;

class Point3D :
	public Primitive3D
{
public:
	Point3D(float x, float y, float z)
		: Primitive3D(x, y, z, 0) 
	{ }

	Point3D(const Point3D& point)
		: Point3D(point._x, point._y, point._z)
	{ }

	bool operator==(const Point3D&);

	Vector3D operator-(const Point3D&);

	Point3D operator-(const Vector3D&);

	Point3D operator+(const Vector3D&);

	friend ostream& operator << (ostream& out, const Point3D& p);
};

