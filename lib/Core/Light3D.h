#pragma once

#include <list>

#include "Object3D.h"

class Light3D :
	public Object3D
{
public:
	Light3D();

	Light3D(const Point3D& position, const Color3D& intensity);


	Light3D(const Point3D& position, const Matrix4d& translate, const Color3D& intensity);

	const Color3D Intensity;

	bool operator==(const Light3D& other) const
	{
		return (Object3D)*this == (Object3D)other && Intensity == other.Intensity;
	}

	Color3D Compute(const Material3D& material, const Point3D& position, const Vector3D& camera, const Vector3D& normal, bool shadow = false) const;

	bool InShadow(const Point3D& point, const std::list<Shape3D*>& shapes) const;

};