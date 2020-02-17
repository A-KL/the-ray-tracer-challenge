#pragma once

#include <iostream>

#include "Primitive3D.h"

using namespace std;

class Vector3D :
	public Primitive3D
{
public:
	Vector3D(float x, float y, float z)
		: _x(x), _y(y), _z(z)
	{ }

	Vector3D(const Vector3D& vector)
		: _x(vector._x), _y(vector._y), _z(vector._z)
	{ }


	inline float X() const { return _x; };

	inline float Y() const { return _y; };

	inline float Z() const { return _z; };

	bool operator==(const Vector3D&);

	Vector3D operator+(const Vector3D&);

	Vector3D operator-(const Vector3D&);

	Vector3D operator*(float);

	friend ostream& operator << (ostream& out, const Vector3D& p);

private:
	float _x, _y, _z;

};

