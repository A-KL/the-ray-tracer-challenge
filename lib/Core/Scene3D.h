#pragma once

#include <list>

#include "Color3D.h"
#include "Shape3D.h"
#include "Light3D.h"
#include "Ray3D.h"
#include "Computation.h"

class Scene3D
{
public:
	std::list<Light3D*> Lights;

	std::list<Shape3D*> Shapes;

	Color3D ColorAt(const Ray3D& ray, int remaining = 4) const;

	Color3D ReflectedAt(const Computation& comp, int remaining = 4) const;

	Color3D RefractedAt(const Computation& comp, const int remaining) const;

	Color3D ShadeHit(const Computation& computation, int remaining = 4) const;
};