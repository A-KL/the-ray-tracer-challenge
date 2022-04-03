#include <list>
#include <math.h>

#include "Mathf.h"
#include "Color3D.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material3D.h"
#include "Shape3D.h"

#include "Ray3D.h"
#include "Intersection.h"
#include "Computation.h"

#include "Light3D.h"

#include "RayTracer.h"


Color3D Light3D::Compute(const Material3D& material, const Point3D& position, const Vector3D& camera, const Vector3D& normal, bool shadow) const
{
	auto effective_color = material.Color * Intensity;

	auto light_direction = Vector3D::Normalize(Position - position);

	auto ambient = effective_color * material.Ambient;

	auto light_dot_normal = Vector3D::Dot(light_direction, normal);

	auto diffuse = Color3D::Black;
	auto specular = Color3D::Black;

	if (!shadow && light_dot_normal >= 0)
	{
		diffuse = effective_color * material.Diffuse * light_dot_normal;

		auto reflect_direction = Vector3D::Reflect(-light_direction, normal);

		auto reflect_dot_camera = Vector3D::Dot(reflect_direction, camera);


		if (reflect_dot_camera > 0)
		{
			auto factor = pow(reflect_dot_camera, material.Shininess);

			specular = Intensity * material.Specular * factor;
		}
	}

	return ambient + diffuse + specular;
}

bool Light3D::InShadow(const Point3D& point, const std::list<Shape3D*>& shapes) const
{
	auto v = Position - point;
	auto distance = v.Magniture();
	auto direction = v.Normalize();

	Ray3D ray(point, direction);

	auto intersections = ray_intersect(shapes, ray);

	auto h = ray_hit(intersections);

	return !h.empty() && (h.begin()->Value < distance);
}