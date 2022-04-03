#pragma once

#include "Object3D.h"

class Shape3D : public Object3D
{
public:
	Shape3D(const Material3D& material);

	Shape3D(const Matrix4d& transform, const Material3D& material);

	Shape3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	const Material3D Material;

	const Vector3D NormalAt(const Point3D& point) const;
	
	bool operator==(const Shape3D& other) const;

protected:
	virtual const Vector3D LocalNormalAt(const Point3D& point) const = 0;
};