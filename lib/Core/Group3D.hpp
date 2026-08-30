#pragma once

#include <vector>
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

  Group3D(const Group3D& group);

  Group3D(const Matrix4d& transform);

  Group3D(const Point3D& position, const Matrix4d& transform);

  Group3D* AddShape(Shape3D& shape);

  Group3D* AddShape(Shape3D* shape);

  const Shape3D* GetShape(int index) const;

  bool operator==(const Group3D& other) const;

  int ShapesCount() const;

  std::vector<Intersection> LocalIntersect(const Ray3D& ray) const;

private:
  std::vector<Shape3D*> _shapes;

  const Vector3D LocalNormalAt(const Point3D& point) const;
};