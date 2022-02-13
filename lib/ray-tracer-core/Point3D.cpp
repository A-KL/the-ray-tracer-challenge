#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

Vector3D Point3D::operator-(const Point3D& other)
{
	return Vector3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

Point3D Point3D::operator+(const Vector3D& other)
{
	return Point3D(X() + other.X(), Y() + other.Y(), Z() + other.Z());
}

Point3D Point3D::operator-(const Vector3D& other)
{
	return Point3D(X() - other.X(), Y() - other.Y(), Z() - other.Z());
}

ostream& operator<<(ostream& out, const Point3D& p)
{
	out << "Point3D";
	out << (Primitive3D<double>)p;

	return out;
}