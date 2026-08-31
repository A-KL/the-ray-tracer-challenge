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
  Shape3D(Material3D::Default),
  TTriangle3D<Point3D>(p1, p2, p3), Normal(ComputeNormal())
{ }

const Vector3D Triangle3D::LocalNormalAt(const Point3D& point) const
{
	return Normal;
}

const  Vector3D Triangle3D::ComputeNormal() const
{
  return E2.Cross(E1).Normalize();
}
