#include <vector>

#include "Primitive3D.h"

Primitive3D Primitive3D::operator-()
{
	return Primitive3D(-_x, -_y, -_z, -_w);
}