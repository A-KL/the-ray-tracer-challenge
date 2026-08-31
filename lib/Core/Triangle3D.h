#pragma once

#include <vector>

#include "Point3D.h"
#include "Vector3D.h"
#include "Intersection.h"
#include "Material3D.h"
#include "MatrixOps.hpp"
#include "Ray3D.h"
#include "Shape3D.h"

#include "TTriangle3D.h"

class SmoothTriangle3D : virtual public TSmoothTriangle3D<Point3D&>
{
};

class RefTriangle3D : virtual public TTriangle3D<Point3D&>
{
  public:
	  RefTriangle3D(const RefTriangle3D& point);

	  RefTriangle3D(Point3D& p1, Point3D& p2, Point3D& p3);

    const Vector3D Normal;
    
  protected:
	  const Vector3D LocalNormalAt(const Point3D& point) const;
    const Vector3D ComputeNormal() const;    
};

class Triangle3D : virtual public Shape3D
{
public:
  Triangle3D(const Triangle3D& point);

	Triangle3D(const Point3D p1, const Point3D p2, const Point3D p3);

	bool operator==(const Triangle3D& other) const;

  std::vector<Intersection> LocalIntersect(const Ray3D& ray) const;

  const Point3D P1;
  const Point3D P2;
  const Point3D P3;

  const Vector3D E1;
  const Vector3D E2;

  const Vector3D Normal;

protected:
	const Vector3D LocalNormalAt(const Point3D& point) const;
  const Vector3D ComputeNormal() const;
};