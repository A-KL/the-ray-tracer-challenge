#include "Mathf.h"

#include "Vector3D.h"

bool Vector3D::operator==(const Vector3D& b)
{
	return 
		Mathf::Approximately(_x, b._x) &&
		Mathf::Approximately(_y, b._y) &&
		Mathf::Approximately(_z, b._z);
}

Vector3D Vector3D::operator+(const Vector3D& v)
{
	return Vector3D(_x + v._x, _y + v._y, _z + v._z);
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
	return Vector3D(_x - v._x, _y - v._y, _z - v._z);
}

Vector3D Vector3D::operator*(float value)
{
	return Vector3D(_x * value, _y * value, _z * value);
}

ostream& operator<<(ostream& out, const Vector3D& p)
{
	out << "vector(";
	out << p._x << ",";
	out << p._y << ",";
	out << p._z;
	out << ")";
	out << endl;

	return out;
}