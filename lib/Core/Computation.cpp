#include <vector>

#include "Mathf.h"
#include "Computation.h"

void Compute_N1_N2(const Intersection& intersection, const std::vector<const Intersection>& intersections, double& n1, double& n2)
{
	std::vector<const Shape3D*> containers;

	for (const Intersection& i : intersections) 
	{
		if (i == intersection)
		{
			n1 = containers.empty() ? 1.0 : containers.back()->Material.RefractiveIndex;
		}

		auto result = std::find(containers.begin(), containers.end(), i.Shape);

		if (result != containers.end())
		{
			containers.erase(result);
		}
		else
		{
			containers.push_back(i.Shape);
		}

		if (i == intersection)
		{
			n2 = containers.empty() ? 1.0 : containers.back()->Material.RefractiveIndex;
		}
	}
}

const double Computation::SchlickValue() const
{
    auto cos = Camera.Dot(Normal);

    if (N1 > N2) 
    {
        auto n = N1 / N2;
        auto sin2_t = n * n * (1.0 - cos * cos);
        if (sin2_t > 1.0) 
            return 1.0; 

		auto cos_t = sqrt(1.0 - sin2_t);
		cos = cos_t;
    }

	auto r0 = pow((N1 - N2) / (N1 + N2), 2);

    return (r0 + (1.0 - r0) * pow((1.0 - cos), 5));
}

const Computation Computation::Prepare(const Intersection& intersection, const Ray3D& ray, const std::vector<const Intersection>& intersections)
{
	auto position = ray.Position(intersection.Value);
	auto normal = intersection.Shape->NormalAt(position);
	auto camera = -ray.Direction;
	auto inside = Vector3D::Dot(normal, camera) < 0;
	normal = inside ? -normal : normal;
	auto over_point = position + normal * Mathf<double>::Epsilon();
	auto under_point = position - normal * Mathf<double>::Epsilon();
	auto reflection = Vector3D::Reflect(ray.Direction, normal);
	auto n1 = 1.0;
	auto n2 = 1.0;

	if (!intersections.empty())
	{
		Compute_N1_N2(intersection, intersections, n1, n2);
	}

	return Computation { intersection, position, over_point, under_point, normal, camera, reflection, inside, n1, n2 };
}

const Computation Computation::Prepare(const Intersection& intersection, const Ray3D& ray)
{
	return Prepare(intersection, ray, std::vector<const Intersection> { intersection });
}