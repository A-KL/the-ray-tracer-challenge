#pragma once

#include <list>

#include "Shape3D.h"
#include "Intersection.h"
#include "Vector3D.h"
#include "Ray3D.h"
#include "MatrixOps.hpp"

class Group3D
  : virtual public Shape3D  
{
public:
  Group3D();

  Group3D(const Matrix4d& transform);

  Group3D(const Point3D& position, const Matrix4d& transform);

  // Group3D(const Material3D& material);

  // Group3D(const Matrix4d& transform, const Material3D& material);

  // Group3D(const Point3D& position, const Matrix4d& transform, const Material3D& material);

  // std::vector<std::shared_ptr<Shape3D>> Shapes;

  // bool operator==(const Group3D& other) const;

  // std::list<Intersection> LocalIntersect(const Ray3D& ray) const;

  // const Vector3D LocalNormalAt(const Point3D& point) const;

};