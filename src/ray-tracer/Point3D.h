#pragma once

#include <iostream>

#include "Primitive3D.h"

using namespace std;

class Point3D :
	public Primitive3D
{
public:
	Point3D(float x, float y, float z)
		: _x(x), _y(y), _z(z)
	{ }

	Point3D(const Point3D& point)
		: _x(point._x), _y(point._y), _z(point._z)
	{ }

	inline float X() const { return _x; };

	inline float Y() const { return _y; };

	inline float Z() const { return _z; };

	bool operator==(const Point3D&);

	Vector3D operator-(const Point3D&);

	Point3D operator-(const Vector3D&);

	Point3D operator+(const Vector3D&);

	friend ostream& operator << (ostream& out, const Point3D& p);

private:
	float _x, _y, _z;
};

