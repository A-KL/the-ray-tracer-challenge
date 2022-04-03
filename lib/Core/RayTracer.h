#pragma once

std::list<Intersection> ray_intersect(const Shape3D* object, const Ray3D& ray);

std::list<Intersection> ray_hit(const std::list<Intersection>& intersections);