#pragma once

#include <vector>

#include "Point3D.h"
#include "Vector3D.h"
#include "Intersection.h"
#include "Material3D.h"
#include "MatrixOps.h"
#include "Ray3D.h"
#include "Shape3D.h"

class TriangleShape3D : virtual public Shape3D
{
  public:

	  TriangleShape3D(const TriangleShape3D& t) :
      TriangleShape3D(t.P1, t.P2, t.P3)
    { }

    TriangleShape3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) : 
      Shape3D(Material3D::Default), P1(p1), P2(p2), P3(p3), E1(p2 - p1), E2(p3 - p1)
    {  }

    bool operator==(const TriangleShape3D& other) const
    {
      return Shape3D::operator==(other) &&
        P1 == other.P1 &&
        P2 == other.P2 &&
        P3 == other.P3;
    }

    const Point3D& P1;
    const Point3D& P2;
    const Point3D& P3;

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

      result.push_back(Intersection(t, this, u, v));

      return result;
    }
};