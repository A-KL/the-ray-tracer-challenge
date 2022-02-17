#pragma once

#include <iostream>
#include <list>
#include <vector>

std::list<Intersection> ray_intersect(const std::list<Shape3D>& objects, const Ray3D& ray);

std::list<Intersection> ray_intersect(const Shape3D& object, const Ray3D& ray);

const std::list<Intersection> ray_hit(const std::list<Intersection>& intersections);