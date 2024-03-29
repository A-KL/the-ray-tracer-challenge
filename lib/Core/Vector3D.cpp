#include "Vector3D.h"

Vector3D Vector3D::operator+(const Vector3D& other) const
{
	return Vector3D(X() + other.X(), Y() + other.Y(), Z() + other.Z());
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

Vector3D Vector3D::operator-() const
{
	return Vector3D(-X(), -Y(), -Z());
}

Vector3D Vector3D::operator*(double value) const
{
	return Vector3D(X() * value, Y() * value, Z() * value);
}

double Vector3D::Magniture() const
{
	return sqrt(pow(X(), 2) + pow(Y(), 2) + pow(Z(), 2) + pow(W(), 2));
}

Vector3D Vector3D::Normalize() const
{
	double m = Magniture();

	return Vector3D(X() / m, Y() / m, Z() / m, W() / m);
}

Vector3D Vector3D::Normalize(const Vector3D& v1)
{
	double m = v1.Magniture();

	return Vector3D(v1.X() / m, v1.Y() / m, v1.Z() / m, v1.W() / m);
}

double Vector3D::Dot(const Vector3D& v1, const Vector3D& v2)
{
	return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z() + v1.W() * v2.W();
}

Vector3D Vector3D::Reflect(const Vector3D& in, const Vector3D& normal)
{
	return in - normal * 2.0 * Dot(in, normal);
}

double Vector3D::Dot(const Vector3D& other) const
{
	return Vector3D::Dot(*this, other);
}

Vector3D Vector3D::Cross(const Vector3D& other) const
{
	return Vector3D(
		Y() * other.Z() - Z() * other.Y(),
		Z() * other.X() - X() * other.Z(),
		X() * other.Y() - Y() * other.X());
}

std::ostream& operator<<(std::ostream& out, const Vector3D& p)
{
	out << "Vector3D";
	out << (Primitive3D<double>)p;

	return out;
}