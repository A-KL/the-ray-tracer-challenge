#pragma once

#include <vector>
#include <algorithm>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.h"

bool UnionRule(bool l_hit, bool in_l, bool in_r);

bool IntersectRule(bool l_hit, bool in_l, bool in_r);

bool DifferenceRule(bool l_hit, bool in_l, bool in_r);

template <typename TFilter>
class CSG
	: virtual public Shape3D
{
public:
  CSG(const CSG& csg) 
    : CSG(csg.Filter, csg.Left, csg.Right, csg.Transformation, csg.Material)
  { }

  CSG(TFilter filter, Shape3D* left, Shape3D* right)
    : CSG(filter, left, right, Matrix4d::Identity(), Material3D::Default)
  { }

  CSG(TFilter filter, Shape3D* left, Shape3D* right, const Matrix4d& transform, const Material3D& material) 
    : Shape3D(transform, material), Left(left), Right(right), Filter(filter)
  { 
    left->Parent = this;
    right->Parent = this;
  }

  Shape3D* Left;
  Shape3D* Right;
  TFilter Filter;

  bool operator==(const CSG& other) const
  {
    return Shape3D::operator==(other) && 
      Filter == other.Filter,
      Left == other.Left &&
      Right == other.Right;
  }

  const bool Contains(const Shape3D* shape) const
  {
    return (Left == shape) || (Right == shape);
  }

  std::vector<Intersection> LocalIntersect(const Ray3D& ray) const
  {
    auto left_xs = Left->Intersect(ray);
    auto right_xs = Right->Intersect(ray);

    copy(right_xs.begin(), right_xs.end(), back_inserter(left_xs));

    std::sort(left_xs.begin(), left_xs.end());
     
    return FilterIntersections(left_xs);
  }

  const Vector3D LocalNormalAt(const Point3D& point, const Intersection* hit) const
  {
    return Vector3D(0,0,0);
  }

// private:

  std::vector<Intersection> FilterIntersections(const std::vector<Intersection>& intersections) const
  {
    // prepare a list to receive the filtered intersections
    std::vector<Intersection> results;
    // begin outside of both children
    auto in_l = false;
    auto in_r = false;

    for (const auto& i :intersections)
    {
      // if i.object is part of the "left" child, then lhit is true
      auto l_hit = Left->Contains(i.Shape);

      if (Filter(l_hit, in_l, in_r)) {
        results.push_back(i);
      }

      // depending on which object was hit, toggle either inl or inr
      if (l_hit) {
        in_l = !in_l;
      } else {
        in_r = !in_r;
      }
    }
    return results;
  }
};