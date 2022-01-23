#include "Vector3D.h"

bool Vector3D::operator==(const Vector3D& other)
{
	return 
		Mathf::Approximately(_x, other._x) &&
		Mathf::Approximately(_y, other._y) &&
		Mathf::Approximately(_z, other._z);
}

Vector3D Vector3D::operator+(const Vector3D& other)
{
	return Vector3D(_x + other._x, _y + other._y, _z + other._z);
}

Vector3D Vector3D::operator-(const Vector3D& other)
{
	return Vector3D(_x - other._x, _y - other._y, _z - other._z);
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

float Vector3D::Dot(const Vector3D& other)
{
	return (_x * other._x) + (_y * other._y) + (_z * other._z) + (_w * other._w);
}

Vector3D Vector3D::Cross(const Vector3D& other)
{
	return Vector3D(
		_x * other._z - _z * other._y,
		_z * other._x - _x * other._z,
		_x * other._y - _y * other._x);
}

ostream& operator<<(ostream& out, const Vector3D& p)
{
	out << "Vector3D";
	out << (Primitive3D<double>)p;

	return out;
}