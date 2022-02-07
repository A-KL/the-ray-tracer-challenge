#pragma once

std::list<Intersection> ray_intersect(const Object3D& object, const Ray3D& ray);

Intersection ray_hit(const std::list<Intersection>& intersections);