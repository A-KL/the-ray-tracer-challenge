#pragma once

class Scene3D
{
public:

	std::list<Light3D*> Lights;

	std::list<Shape3D*> Shapes;

	Color3D ColorAt(const Ray3D& ray) const
	{
		auto intersects = ray_intersect(Shapes, ray);

		auto hits = ray_hit(intersects);

		if (hits.empty())
		{
			return Color3D::Black;
		}

		auto computation = Computation::Prepare(*hits.begin(), ray);

		return ShadeHit(computation);
	}

	Color3D ShadeHit(const Computation& computation) const
	{
		Color3D result(0, 0, 0);

		for (auto& light : Lights)
		{
			auto is_shadow = light
				->InShadow(computation.OverPosition, Shapes);

			result += light
				->Compute(computation.Intersect.Shape->Material, computation.OverPosition, computation.Camera, computation.Normal, is_shadow);
		}

		return result;
	}
};