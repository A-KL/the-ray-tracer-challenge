#include "Mathf.h"
#include "Primitive3D.h"

#include "Vector3D.h"

Vector3D Vector3D::operator+(const Vector3D& other)
{
	return Vector3D(X() + other.X(), Y() + other.Y(), Z() + other.Z());
}

Vector3D Vector3D::operator-(const Vector3D& other)
{
	return Vector3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

Vector3D Vector3D::operator*(float value)
{
	return Vector3D(X() * value, Y() * value, Z() * value);
}

float Vector3D::Magniture()
{
	return sqrtf(powf(X(), 2) + powf(Y(), 2) + powf(Z(), 2) + powf(W(), 2));
}

Vector3D Vector3D::Normalize()
{
	float m = Magniture();

	return Vector3D(X() / m, Y() / m, Z() / m, W() / m);
}

float Vector3D::Dot(const Vector3D& v1, const Vector3D& v2)
{
	return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z() + v1.W() * v2.W();
}

float Vector3D::Dot(const Vector3D& other)
{
	return Vector3D::Dot(*this, other);
}

Vector3D Vector3D::Cross(const Vector3D& other)
{
	return Vector3D(
		X() * other.Z() - Z() * other.Y(),
		Z() * other.X() - X() * other.Z(),
		X() * other.Y() - Y() * other.X());
}

ostream& operator<<(ostream& out, const Vector3D& p)
{
	out << "Vector3D";
	out << (Primitive3D<double>)p;

	return out;
}