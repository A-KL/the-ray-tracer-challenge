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
#include "Sphere3D.h"

bool Sphere3D::operator==(const Sphere3D& other) const
{
	return (Shape3D)*this == other;
}

