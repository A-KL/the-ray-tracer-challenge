#include "Computation.h"

#include "Mathf.h"

const Computation Computation::Prepare(const Intersection& intersection, const Ray3D& ray)
{
	auto position = ray.Position(intersection.Value);
	auto normal = intersection.Shape->NormalAt(position);
	auto camera = -ray.Direction;
	auto inside = Vector3D::Dot(normal, camera) < 0;
	normal = inside ? -normal : normal;
	auto over_point = position + normal * Mathf<double>::Epsilon();
	auto reflection = Vector3D::Reflect(ray.Direction, normal);

	return Computation{ intersection, position, over_point, normal, camera, reflection, inside };
}