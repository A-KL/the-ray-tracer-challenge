#pragma once

#include "Point3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Matrix.hpp"

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
		_material(material)
	{ }

	inline Material GetMaterial() const
	{
		return _material;
	}

	bool operator==(const Shape3D& other) const
	{
		return ((Object3D)*this) == other && _material == other._material;
	}

private:
	Material _material;
};