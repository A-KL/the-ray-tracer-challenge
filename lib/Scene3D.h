#pragma once

class Scene3D
{
public:

	std::list<Light3D> Lights;

	std::list<Shape3D> Shapes;

	Color3D ColorAt(const Ray3D& ray) const
	{
		auto intersects = ray_intersect(Shapes, ray);

		auto hits = ray_hit(intersects);

		if (hits.empty())
		{
			return Color3D::Black;
		}

		auto computation = Computation::Prepare(*hits.begin(), ray);

		return shade_hit(Lights, computation);
	}
};