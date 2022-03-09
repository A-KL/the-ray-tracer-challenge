#include <math.h>
#include "Mathf.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Environment.h"
#include "Projectile.h"

Projectile Projectile::Tick(const Environment& env) const
{
	return Projectile(_position + _velocity, _velocity + env.Gravity + env.Wind);
}