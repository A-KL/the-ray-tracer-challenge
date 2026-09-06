#pragma once

#include <vector>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.h"

bool UnionRule(bool l_hit, bool in_l, bool in_r) {
  return (l_hit && !in_r) || (!l_hit && !in_l);
}

bool IntersectRule(bool l_hit, bool in_l, bool in_r) {
  return (l_hit && in_r) || (!l_hit && in_l);
}

bool DefaultRuleRule(bool l_hit, bool in_l, bool in_r) {
  return false;
}

class CSG
	: virtual public Shape3D
{
public:
  CSG(const CSG& csg);

  CSG(Shape3D* left, Shape3D* right);

  CSG(Shape3D* left, Shape3D* right, const Matrix4d& transform, const Material3D& material);

  Shape3D* Left;
  Shape3D* Right;

  bool operator==(const CSG& other) const;

  const bool Contains(const Shape3D* shape) const;

	std::vector<Intersection> LocalIntersect(const Ray3D& ray) const;

	const Vector3D LocalNormalAt(const Point3D& point, const Intersection* hit = nullptr) const;
};

template <typename TFilter>
std::vector<Intersection> FilterIntersections(TFilter filter, const CSG& csg, const std::vector<Intersection>& intersections) {

  // prepare a list to receive the filtered intersections
  std::vector<Intersection> results;
  // begin outside of both children
  auto in_l = false;
  auto in_r = false;

  for (auto& i :intersections)
  {
    // if i.object is part of the "left" child, then lhit is true
    auto l_hit = csg.Left->Contains(i.Shape);

    if (filter(l_hit, in_l, in_r)) {
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