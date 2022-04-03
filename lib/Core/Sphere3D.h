#pragma once

#include "Shape3D.h"

class Sphere3D
	: virtual public Shape3D
{
public:
	Sphere3D();

	Sphere3D(Matrix4d& transform);

	Sphere3D(const Material3D& material);

	Sphere3D(const Matrix4d& transform, const Material3D& material);

	Sphere3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	bool operator==(const Sphere3D& other) const;

protected:
	const Vector3D LocalNormalAt(const Point3D& point) const;
};