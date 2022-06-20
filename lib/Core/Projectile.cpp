#include "Projectile.h"

Projectile Projectile::Tick(const Environment& env) const
{
	return Projectile(_position + _velocity, _velocity + env.Gravity + env.Wind);
}