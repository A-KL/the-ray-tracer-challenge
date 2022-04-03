#pragma once

#include "Shape3D.h"

class Plane3D
	: virtual public Shape3D
{
public:
	Plane3D();

	Plane3D(Matrix4d& transform);

	Plane3D(const Material3D& material);

	Plane3D(const Matrix4d& transform, const Material3D& material);

	Plane3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	bool operator==(const Plane3D& other) const;

protected:
	const Vector3D LocalNormalAt(const Point3D& point) const;
};