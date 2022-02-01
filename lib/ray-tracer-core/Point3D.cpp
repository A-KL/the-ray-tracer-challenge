#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

Vector3D Point3D::operator-(const Point3D& b)
{
	return Vector3D(X() - b.X(), Y() - b.Y(), Z() - b.Z());
}

Point3D Point3D::operator+(const Vector3D& b)
{
	return Point3D(X() + b.X(), Y() + b.Y(), Z() + b.Z());
}

Point3D Point3D::operator-(const Vector3D& b)
{
	return Point3D(X() - b.X(), Y() - b.Y(), Z() - b.Z());
}

ostream& operator<<(ostream& out, const Point3D& p)
{
	out << "Point3D";
	out << (Primitive3D<double>)p;

	return out;
}