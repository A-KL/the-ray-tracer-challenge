#include "CSG.h"

CSG::CSG(const CSG& csg) 
  : CSG(csg.Left, csg.Right, csg.Transformation, csg.Material)
{ }

CSG::CSG(Shape3D* left, Shape3D* right)
  : CSG(left, right, Matrix4d::Identity(), Material3D::Default)
{ }

CSG::CSG(Shape3D* left, Shape3D* right, const Matrix4d& transform, const Material3D& material) 
  : Shape3D(transform, material), Left(left), Right(right)
{ 
  left->Parent = this;
  right->Parent = this;
}

bool CSG::operator==(const CSG& other) const
{
	return Shape3D::operator==(other) && 
    Left == other.Left &&
    Right == other.Right;
}

const bool CSG::Contains(const Shape3D* shape) const
{
  return (Left == shape) || (Right == shape);
}

std::vector<Intersection> CSG::LocalIntersect(const Ray3D& ray) const
{
  std::vector<Intersection> intersections;

  return intersections;
}

const Vector3D CSG::LocalNormalAt(const Point3D& point, const Intersection* hit) const
{
  return Vector3D(0,0,0);
}