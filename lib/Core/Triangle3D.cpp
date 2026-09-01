#include "Triangle3D.h"

SmoothTriangle3D::SmoothTriangle3D(
    const SmoothTriangle3D& t) 
    : SmoothTriangle3D(t.P1, t.P2, t.P3, t.N1, t.N2, t.N3)
  { }

SmoothTriangle3D::SmoothTriangle3D(
      const Point3D& p1, const Point3D& p2, const Point3D& p3, 
      const Vector3D& n1, const Vector3D& n2, const Vector3D& n3) 
      : Shape3D(Material3D::Default), TriangleShape3D(p1, p2, p3), N1(n1), N2(n2), N3(n3)
    { }

bool SmoothTriangle3D::operator==(const SmoothTriangle3D& other) const
{
  return TriangleShape3D::operator==(other) &&
    N1 == other.N1 &&
    N2 == other.N2 &&
    N3 == other.N3;
}

const Vector3D SmoothTriangle3D::LocalNormalAt(const Point3D& point) const
{
  return Vector3D(1,1,1);
}

/* Triangle3D */

Triangle3D::Triangle3D(const Triangle3D& t) :
  Triangle3D(t.P1, t.P2, t.P3)
{ }

Triangle3D::Triangle3D(
  const Point3D& p1, const Point3D& p2, const Point3D& p3) 
  : Shape3D(Material3D::Default), TriangleShape3D(p1, p2, p3), Normal(ComputeNormal())
{ }

const Vector3D Triangle3D::LocalNormalAt(const Point3D& point) const
{
	return Normal;
}

const  Vector3D Triangle3D::ComputeNormal() const
{
  return E2.Cross(E1).Normalize();
}
