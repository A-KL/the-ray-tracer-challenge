#include "Point3D.h"

bool Point3D::operator==(const Point3D& b)
{
	return
		Mathf::Approximately(_x, b._x) &&
		Mathf::Approximately(_y, b._y) &&
		Mathf::Approximately(_z, b._z);
}

Vector3D Point3D::operator-(const Point3D& b)
{
	return Vector3D(_x - b._x, _y - b._y, _z - b._z);
}

Point3D Point3D::operator+(const Vector3D& b)
{
	return Point3D(_x + b.X(), _y + b.Y(), _z + b.Z());
}

Point3D Point3D::operator-(const Vector3D& b)
{
	return Point3D(_x - b.X(), _y - b.Y(), _z - b.Z());
}

ostream& operator<<(ostream& out, const Point3D& p)
{
	out << "point(" ;
	out << p._x << ",";
	out << p._y << ",";
	out << p._z;
	out << ")";
	out << endl;

	return out;
}
