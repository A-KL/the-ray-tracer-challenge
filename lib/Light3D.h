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
		Light3D(position, Matrix4d::Identity(), intensity)
	{ }


	Light3D(const Point3D& position, const Matrix4d& translate, const Color3D& intensity) :
		Object3D(position, translate),
		Intensity(intensity)
	{ }

	const Color3D Intensity;


	bool operator==(const Light3D& other) const
	{
		return (Object3D)*this == (Object3D)other && Intensity == other.Intensity;
	}

	Color3D Compute(const Material& material, const Point3D& position, const Vector3D& camera, const Vector3D& normal) const;

};