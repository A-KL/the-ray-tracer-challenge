#pragma once

#include <iostream>
#include <list>

std::list<Intersection> ray_intersect(const std::list<Shape3D>& objects, const Ray3D& ray);

std::list<Intersection> ray_intersect(const Shape3D& object, const Ray3D& ray);

const std::list<Intersection> ray_hit(const std::list<Intersection>& intersections);

const Color3D shade_hit(const std::list<Light3D>& lights, const Computation& computation);

const Matrix4d view_transform(const Point3D& from, const Point3D& to, const Vector3D& up);