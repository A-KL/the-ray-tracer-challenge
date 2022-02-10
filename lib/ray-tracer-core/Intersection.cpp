#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Sphere3D.h"
#include "Intersection.h"

const Intersection Intersection::Empty = Intersection(0, 0);