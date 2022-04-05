#include "Point3D.h"

const Point3D Point3D::Origin(0, 0, 0);

Vector3D Point3D::operator-(const Point3D& other) const
{
	return Vector3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

Point3D Point3D::operator+(const Vector3D& other) const
{
	return Point3D(X() + other.X(), Y() + other.Y(), Z() + other.Z());
}

Point3D Point3D::operator-(const Vector3D& other) const
{
	return Point3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

bool Point3D::operator==(const Point3D& other) const
{
	return (Primitive3D<double>) *this == (Primitive3D<double>)other;
}

std::ostream& operator<<(std::ostream& out, const Point3D& p)
{
	out << "Point3D";
	out << (Primitive3D<double>)p;

	return out;
}