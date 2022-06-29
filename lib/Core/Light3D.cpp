#include "Light3D.h"

#include "Ray3D.h"
#include "RayTracer.h"

Light3D::Light3D() :
	Light3D(Point3D(0, 0, 0), 1)
{ }

Light3D::Light3D(const Point3D& position, const Color3D& intensity) :
	Light3D(position, Matrix4d::Identity(), intensity)
{ }


Light3D::Light3D(const Point3D& position, const Matrix4d& translate, const Color3D& intensity) :
	Object3D(position, translate),
	Intensity(intensity)
{ }

Color3D Light3D::Compute(const Material3D& material, const Shape3D& shape, const Point3D& position, const Vector3D& camera, const Vector3D& normal, bool shadow) const
{
	auto effective_color = material.Pattern->at_shape(position, shape) * Intensity;

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

	auto intersections = ray.Intersect(shapes);

	auto h = ray_hit(intersections);

	return !h.empty() && (h.begin()->Value < distance);
}