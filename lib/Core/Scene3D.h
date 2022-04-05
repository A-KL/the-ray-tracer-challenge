#pragma once

#include <list>

#include "Light3D.h"
#include "Ray3D.h"
#include "Computation.h"

class Scene3D
{
public:
	std::list<Light3D*> Lights;

	std::list<Shape3D*> Shapes;

	Color3D ColorAt(const Ray3D& ray) const;

	Color3D ShadeHit(const Computation& computation) const;
};