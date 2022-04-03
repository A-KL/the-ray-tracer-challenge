#include <math.h>

#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material3D.h"
#include "Shape3D.h"
#include "Intersection.h"

Intersection::Intersection(double t, const Shape3D& object)
	: Value(t), Shape(&object)
{ }

Intersection::Intersection(double t, const Shape3D* object)
	: Value(t), Shape(object)
{ }

bool Intersection::operator==(const Intersection& other) const
{
	return Value == other.Value && Shape == other.Shape;
}

bool Intersection::operator!=(const Intersection& other) const
{
	return !(*this == other);
}

//bool Intersection::operator>(const Intersection& other) const
//{
//	return Value > other.Value;
//}
//
//bool Intersection::operator<(const Intersection& other) const
//{
//	return Value < other.Value;
//}