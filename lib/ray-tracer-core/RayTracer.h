#pragma once

std::list<Intersection> ray_intersect(const Sphere3D& object, const Ray3D& ray);

Intersection ray_hit(const std::list<Intersection>& intersections);