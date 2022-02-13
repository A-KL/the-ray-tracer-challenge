#pragma once

#include "Object3D.h"

class Light3D :
	public Object3D
{
public:
	Light3D() :
		Light3D(Point3D(0, 0, 0), 1)
	{ }

	Light3D(const Point3D& position, int intensity) :
		Object3D(position),
		_intensity(intensity)
	{ }


	Light3D(const Point3D& position, const Matrix4d& translate, int intensity) :
		Object3D(position, translate),
		_intensity(intensity)
	{ }

	inline int Intensity() const
	{
		return _intensity;
	}

	bool operator==(const Object3D& other) const
	{
		return false;
	}

	bool operator==(const Light3D& other) const
	{
		return (Object3D)*this == (Object3D)other && _intensity == other._intensity;
	}

private:
	int _intensity;

};