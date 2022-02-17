#pragma once

class World3D
{
public:

	std::list<Light3D> Lights;

	std::list<Shape3D> Shapes;

	//Color3D Intersect(const Ray3D& ray) const;
};