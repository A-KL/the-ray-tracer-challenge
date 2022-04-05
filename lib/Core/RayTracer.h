#pragma once

#include <list>

#include "Intersection.h"
#include "Shape3D.h"
#include "Ray3D.h"

std::list<Intersection> ray_intersect(const Shape3D* object, const Ray3D& ray);

std::list<Intersection> ray_hit(const std::list<Intersection>& intersections);