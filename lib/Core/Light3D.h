#pragma once

#include <list>

#include "Color3D.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "MatrixOps.hpp"
#include "Material3D.h"
#include "Shape3D.h"
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

	Color3D Compute(const Material3D& material, const Shape3D& shape, const Point3D& position, const Vector3D& camera, const Vector3D& normal, bool shadow = false) const;

	bool InShadow(const Point3D& point, const std::list<Shape3D*>& shapes) const;

};