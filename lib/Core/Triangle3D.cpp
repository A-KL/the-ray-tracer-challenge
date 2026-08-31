#include "Triangle3D.h"

/* RefTriangle3D */

RefTriangle3D::RefTriangle3D(const RefTriangle3D& t) :
  RefTriangle3D(t.P1, t.P2, t.P3)
{ }

RefTriangle3D::RefTriangle3D(Point3D& p1, Point3D& p2, Point3D& p3) :
	Shape3D(Material3D::Default),
	TTriangle3D<Point3D&>(p1, p2, p3),
	Normal(ComputeNormal())
{ }

const Vector3D RefTriangle3D::LocalNormalAt(const Point3D& point) const
{
	return Normal;
}

const  Vector3D RefTriangle3D::ComputeNormal() const
{
  return E2.Cross(E1).Normalize();
}

/* Triangle3D */

Triangle3D::Triangle3D(const Triangle3D& t) :
  Triangle3D(t.P1, t.P2, t.P3)
{ }

Triangle3D::Triangle3D(const Point3D p1, const Point3D p2, const Point3D p3) :
	Shape3D(Material3D::Default), P1(p1), P2(p2), P3(p3), E1(p2 - p1), E2(p3 - p1), Normal(ComputeNormal())
{ }

bool Triangle3D::operator==(const Triangle3D& other) const
{
	return Shape3D::operator==(other) &&
		P1 == other.P1 &&
		P2 == other.P2 &&
		P3 == other.P3;
}

const Vector3D Triangle3D::LocalNormalAt(const Point3D& point) const
{
	return Normal;
}

std::vector<Intersection> Triangle3D::LocalIntersect(const Ray3D& ray) const
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

const  Vector3D Triangle3D::ComputeNormal() const
{
  return E2.Cross(E1).Normalize();
}
