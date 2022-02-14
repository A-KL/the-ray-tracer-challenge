#include <math.h>

#include "Mathf.h"

#include "Color3D.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material.h"

#include "Light3D.h"

Color3D Light3D::Compute(const Material& material, const Point3D& position, const Vector3D& camera, const Vector3D& normal) const
{
	auto effective_color = material.Color * _intensity;

	auto light_direction = Vector3D::Normalize(Location() - position);

	auto ambient = effective_color * material.Ambient;

	auto light_dot_normal = Vector3D::Dot(light_direction, normal);

	auto diffuse = Color3D::Black;
	auto specular = Color3D::Black;

	if (light_dot_normal >= 0)
	{
		diffuse = effective_color * material.Diffuse * light_dot_normal;

		auto reflect_direction = Vector3D::Reflect(-light_direction, normal);

		auto reflect_dot_camera = Vector3D::Dot(reflect_direction, camera);


		if (reflect_dot_camera > 0)
		{
			auto factor = pow(reflect_dot_camera, material.Shininess);

			specular = _intensity * material.Specular * factor;
		}
	}

	return ambient + diffuse + specular;
}