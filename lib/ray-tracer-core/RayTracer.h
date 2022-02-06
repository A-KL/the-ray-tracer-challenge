#pragma once

std::list<Intersection> ray_intersect(const Object3D& object, const Ray3D& ray)
{
	Vector3D object_to_ray = ray.Location() - object.Location();

	float a = Vector3D::Dot(ray.Direction(), ray.Direction());

	float b = 2 * Vector3D::Dot(ray.Direction(), object_to_ray);

	float c = Vector3D::Dot(object_to_ray, object_to_ray) - 1;

	float d = powf(b, 2) - 4 * a * c;

	std::list<Intersection> result;

	if (d >= 0)
	{
		double t1 = (-b - sqrtf(d)) / (2 * a);
		double t2 = (-b + sqrtf(d)) / (2 * a);

		result = {
			Intersection(t1, object),
			Intersection(t2, object)
		};
	}

	return result;
}

Intersection ray_hit(std::list<Intersection>& intersections)
{	
	intersections.sort(IntersectionComparator());

	for (auto &intersection : intersections)
	{
		if (intersection.T() >= 0)
		{
			return intersection;
		}
	}

	return Intersection::Empty;
}