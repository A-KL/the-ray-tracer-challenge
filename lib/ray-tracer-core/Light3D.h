#pragma once

#include "Object3D.h"

class Light3D :
	public Object3D
{
public:
	Light3D() :
		Light3D(Point3D(0, 0, 0), 1)
	{ }

	Light3D(const Point3D& position, const Color3D& intensity) :
		Object3D(position),
		_intensity(intensity)
	{ }


	Light3D(const Point3D& position, const Matrix4d& translate, const Color3D& intensity) :
		Object3D(position, translate),
		_intensity(intensity)
	{ }

	inline Color3D Intensity() const
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

	Color3D Compute(const Material& material, const Point3D& position, const Vector3D& camera, const Vector3D& normal) const;

private:
	Color3D _intensity;

};