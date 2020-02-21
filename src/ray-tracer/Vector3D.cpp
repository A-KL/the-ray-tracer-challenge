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

float Vector3D::Magniture()
{
	return sqrtf(powf(_x, 2) + powf(_y, 2) + powf(_z, 2) + powf(_w, 2));
}

Vector3D Vector3D::Normalize()
{
	float m = Magniture();

	return Vector3D(_x / m, _y / m, _z / m, _w / m);
}

float Vector3D::Dot(const Vector3D& v)
{
	return (_x * v._x) + (_y * v._y) + (_z * v._z) + (_w * v._w);
}

Vector3D Vector3D::Cross(const Vector3D& v)
{
	return Vector3D(
		_x * v._z - _z * v._y,
		_z * v._x - _x * v._z,
		_x * v._y - _y * v._x);
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