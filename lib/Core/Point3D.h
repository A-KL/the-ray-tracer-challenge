#pragma once

#include <iostream>
#include <math.h>
#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"

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

	Vector3D operator-(const Point3D& point) const;

	Point3D operator-(const Vector3D& other) const;

	Point3D operator+(const Vector3D& other) const;

	bool operator==(const Point3D& other) const;

	const static Point3D Origin;

	friend std::ostream& operator<<(std::ostream& out, const Point3D& p);
};

