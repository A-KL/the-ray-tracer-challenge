#include <math.h>
#include "Mathf.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Object3D.h"

bool Object3D::operator==(const Object3D& other) const
{
	return
		Position == other.Position &&
		Transformation == other.Transformation;
}