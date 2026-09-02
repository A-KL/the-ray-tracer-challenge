#pragma once

#include <vector>

#include "Point3D.h"
#include "Vector3D.h"
#include "Intersection.h"
#include "Material3D.h"
#include "MatrixOps.h"
#include "Ray3D.h"
#include "Shape3D.h"
#include "TriangleShape3D.h"

class SmoothTriangle3D : virtual public TriangleShape3D
{
  public:

	  SmoothTriangle3D(const SmoothTriangle3D& t);

	  SmoothTriangle3D(
      const Point3D& p1, const Point3D& p2, const Point3D& p3, 
      const Vector3D& n1, const Vector3D& n2, const Vector3D& n3);

    bool operator==(const SmoothTriangle3D& other) const;

    const Vector3D& N1;
    const Vector3D& N2;
    const Vector3D& N3;
    
  protected:
    const Vector3D LocalNormalAt(const Point3D& point, const Intersection* hit = nullptr) const;
};

class Triangle3D : virtual public TriangleShape3D
{
  public:
    Triangle3D(const Triangle3D& point);

    Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3);

    const Vector3D Normal;

  protected:
    const Vector3D LocalNormalAt(const Point3D& point, const Intersection* hit = nullptr) const;
    const Vector3D ComputeNormal() const;
};