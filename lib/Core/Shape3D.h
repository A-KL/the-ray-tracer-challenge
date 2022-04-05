#pragma once

#include <list>
#include "Point3D.h"
#include "Vector3D.h"
#include "Object3D.h"
#include "Material3D.h"
#include "MatrixOps.hpp"

class Shape3D : public Object3D
{
public:
	Shape3D(const Material3D& material);

	Shape3D(const Matrix4d& transform, const Material3D& material);

	Shape3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

	const Material3D Material;

	const Vector3D NormalAt(const Point3D& point) const;

	//std::list<Intersection> Intersect(const Ray3D& ray) const;
	
	bool operator==(const Shape3D& other) const;

protected:
	virtual const Vector3D LocalNormalAt(const Point3D& point) const = 0;

	//virtual std::list<Intersection> LocalIntersect(const Ray3D& ray) const = 0;
};