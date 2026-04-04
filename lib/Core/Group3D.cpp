#include "Group3D.hpp"

#include <math.h>
#include "Mathf.h"

Group3D::Group3D() :
    Group3D(Matrix4d::Identity())
{ }

Group3D::Group3D(const Matrix4d& transform) :
    Group3D(Point3D::Origin, transform)
{ }

Group3D::Group3D(const Point3D& position, const Matrix4d& transform) :
	Shape3D(position, transform, Material3D::Default)
{ }