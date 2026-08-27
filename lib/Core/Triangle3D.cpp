#include "Triangle3D.h"

Triangle3D::Triangle3D(const Point3D p1, const Point3D p2, const Point3D p3) :
	Shape3D(Material3D::Default), p1(p1), p2(p2), p3(p3), e1(p2 - p1), e2(p3 - p1), Normal(ComputeNormal())
{ }

bool Triangle3D::operator==(const Triangle3D& other) const
{
	return Shape3D::operator==(other) &&
		p1 == other.p1 &&
		p2 == other.p2 &&
		p3 == other.p3;
}

const Vector3D Triangle3D::LocalNormalAt(const Point3D& point) const
{
	return Normal;
}

const Point3D Triangle3D::GetP1() const
{
  return p1;
}

const Point3D Triangle3D::GetP2() const
{
  return p2;
}

const Point3D Triangle3D::GetP3() const
{
  return p3;
}

std::vector<Intersection> Triangle3D::LocalIntersect(const Ray3D& ray) const
{
	std::vector<Intersection> result;

  auto dir_cross_e2 = ray.Direction.Cross(e2);

  auto det = e1.Dot(dir_cross_e2);

  if (fabs(det) < Mathf<double>::Epsilon()) 
  {
    return result;
  }

  auto f = 1.0 / det;
  auto p1_to_origin = ray.Location - p1;
  auto u = f * p1_to_origin.Dot(dir_cross_e2);

  if (u < 0 || u > 1) 
  {
    return result;
  }

  auto origin_cross_e1 = p1_to_origin.Cross(e1);
  auto v = f * ray.Direction.Dot(origin_cross_e1);

  if (v < 0 or (u + v) > 1)
  {
    return result;
  }

  auto t = f * e2.Dot(origin_cross_e1);

	result.push_back(Intersection(t, this));

	return result;
}

const  Vector3D Triangle3D::ComputeNormal() const
{
  return e2.Cross(e1).Normalize();
}
