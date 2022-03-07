#pragma once

#include "Object3D.h"

class Shape3D : public Object3D
{
public:
	Shape3D(const Material& material) :
		Shape3D(Point3D::Origin, Matrix4d::Identity(), material)
	{}

	Shape3D(const Matrix4d& transform, const Material& material) :
		Shape3D(Point3D::Origin, transform, material)
	{}

	Shape3D(const Point3D& position, const Matrix4d& transform, const Material& material) :
		Object3D(position, transform),
		Mat(material)
	{ }

	const Material Mat;

	virtual const Vector3D NormalAt(const Point3D& point) const;

	bool operator==(const Shape3D& other) const;
};