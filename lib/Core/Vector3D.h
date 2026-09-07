#pragma once

#include <math.h>
#include <iostream>

#include "Mathf.h"
#include "Primitive3D.h"

class Vector3D : public Primitive3D<double>
{
public:
	Vector3D(const Vector3D& vector);

	Vector3D(double x, double y, double z);

	double Magnitude() const;

	Vector3D Normalize() const;

	double Dot(const Vector3D&) const;

	static double Dot(const Vector3D& v1, const Vector3D& v2);

	static Vector3D Reflect(const Vector3D& v1, const Vector3D& v2);

	static Vector3D Normalize(const Vector3D& v1);

	Vector3D Cross(const Vector3D&) const;

	Vector3D operator+(const Vector3D&) const;

	Vector3D operator-(const Vector3D&) const;

	Vector3D operator-() const;

	Vector3D operator*(double) const;

	friend std::ostream& operator<<(std::ostream& out, const Vector3D& p);

protected:
	Vector3D(double x, double y, double z, double w);
};

