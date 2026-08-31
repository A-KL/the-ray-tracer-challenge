#pragma once

#include <vector>

#include "Point3D.h"
#include "Vector3D.h"
#include "Intersection.h"
#include "Material3D.h"
#include "MatrixOps.hpp"
#include "Ray3D.h"
#include "Shape3D.h"

template <typename TPoint3D>
class TTriangle3D : virtual public Shape3D
{
  public:

	  TTriangle3D(
      const TTriangle3D& t) :
      TTriangle3D(t.P1, t.P2, t.P3)
    { }

    TTriangle3D(
      const TPoint3D p1, const TPoint3D p2, const TPoint3D p3) : 
      Shape3D(Material3D::Default), P1(p1), P2(p2), P3(p3), E1(p2 - p1), E2(p3 - p1)
    {  }

    bool operator==(const TTriangle3D& other) const
    {
      return Shape3D::operator==(other) &&
        P1 == other.P1 &&
        P2 == other.P2 &&
        P3 == other.P3;
    }

    const TPoint3D P1;
    const TPoint3D P2;
    const TPoint3D P3;

    const Vector3D E1;
    const Vector3D E2;

    std::vector<Intersection> LocalIntersect(const Ray3D& ray) const
    {
      std::vector<Intersection> result;

      auto dir_cross_e2 = ray.Direction.Cross(E2);

      auto det = E1.Dot(dir_cross_e2);

      if (fabs(det) < Mathf<double>::Epsilon()) 
      {
        return result;
      }

      auto f = 1.0 / det;
      auto p1_to_origin = ray.Location - P1;
      auto u = f * p1_to_origin.Dot(dir_cross_e2);

      if (u < 0 || u > 1) 
      {
        return result;
      }

      auto origin_cross_e1 = p1_to_origin.Cross(E1);
      auto v = f * ray.Direction.Dot(origin_cross_e1);

      if (v < 0 or (u + v) > 1)
      {
        return result;
      }

      auto t = f * E2.Dot(origin_cross_e1);

      result.push_back(Intersection(t, this));

      return result;
    }
};

template <typename TPoint3D>
class TSmoothTriangle3D : virtual public TTriangle3D<TPoint3D>
{
  public:
	  TSmoothTriangle3D(const TSmoothTriangle3D& t) 
    : TSmoothTriangle3D(t.P1, t.P2, t.P3, t.N1, t.N2, t.N3)
    { }

	  TSmoothTriangle3D(
      const TPoint3D p1, const TPoint3D p2, const TPoint3D p3, 
      const Vector3D n1, const Vector3D n2, const Vector3D n3) : 
      TTriangle3D<TPoint3D>(p1, p2, p3), N1(n1), N2(n2), N3(n3)
    {  }

    bool operator==(const TSmoothTriangle3D& other) const
    {
      return TTriangle3D<TPoint3D>::operator==(other) &&
        N1 == other.N1 &&
        N2 == other.N2 &&
        N3 == other.N3;
    }

    const Vector3D N1;
    const Vector3D N2;
    const Vector3D N3;
    
  protected:
    const Vector3D LocalNormalAt(const Point3D& point) const
    {
      return Vector3D::Z;
    }
};