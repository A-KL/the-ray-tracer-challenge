#include "Mathf.h"
#include "Color3D.h"
#include "Material.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Shape3D.h"

bool Shape3D::operator==(const Shape3D& other) const
{
	return ((Object3D)*this) == other && Mat == other.Mat;
}