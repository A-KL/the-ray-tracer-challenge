#pragma once

#include <list>

#include "Point3D.h"
#include "Vector3D.h"
#include "Intersection.h"
#include "Material3D.h"
#include "MatrixOps.hpp"
#include "Ray3D.h"
#include "Shape3D.h"
#include "Vector3D.h"

class Triangle3D : virtual public Shape3D
{
public:
	Triangle3D(const Point3D p1, const Point3D p2, const Point3D p3);

  // Triangle3D(const Point3D* p1, const Point3D* p2, const Point3D* p3);
  // Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3);

  // Triangle3D(const Material3D material);

	// Triangle3D(const Matrix4d transform, const Material3D material);

	// Triangle3D(const Point3D position, const Matrix4d transform, const Material3D material);

	bool operator==(const Triangle3D& other) const;

  const Vector3D Normal;

  std::vector<Intersection> LocalIntersect(const Ray3D& ray) const;

  const Point3D GetP1() const;
  const Point3D GetP2() const;
  const Point3D GetP3() const;

protected:
	const Vector3D LocalNormalAt(const Point3D& point) const;

private:
  const Point3D p1;
  const Point3D p2;
  const Point3D p3;

  const Vector3D e1;
  const Vector3D e2;
  // const Vector3D e3;

  const Vector3D ComputeNormal() const;
};