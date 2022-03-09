#include <list>

#include "Mathf.h"
#include "Color3D.h"
#include "Canvas.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Material.h"
#include "Object3D.h"
#include "Shape3D.h"

#include "Light3D.h"
#include "Ray3D.h"
#include "Intersection.h"
#include "Computation.h"

#include "RayTracer.h"
#include "Scene3D.h"
#include "Camera.h"

Camera::Camera(int h, int v, double fow, const Point3D& from, const Point3D& to, const Vector3D& up)
	: Camera(h, v, fow, ViewTransform(from, to, up))
{ }

Camera::Camera(int h, int v, double fow, const Matrix4d& transformation)
	: HSize(h), VSize(v), Transformation(transformation), FieldOfView(fow), _pixelSize(0) 
{
	auto half_view = tan(fow / 2);
	auto aspect = (double)h / v;

	if (aspect >= 1)
	{
		half_w = half_view;
		half_h = half_view / aspect;
	}
	else
	{
		half_w = half_view * aspect;
		half_h = half_view;
	}

	_pixelSize = half_w * 2 / h;
}

Matrix4d Camera::ViewTransform(const Point3D& from, const Point3D& to, const Vector3D& up)
{
	auto forward = Vector3D::Normalize(to - from);
	auto upn = up.Normalize();
	auto left = forward.Cross(upn);
	auto true_up = left.Cross(forward);
	auto orientation = Matrix4d
	{
		left.X(), left.Y(), left.Z(), 0,
		true_up.X(), true_up.Y(), true_up.Z(), 0,
		-forward.X(), -forward.Y(), -forward.Z(), 0,
		0, 0, 0, 1
	};

	return orientation * Matrix4d::Translate(-from.X(), -from.Y(), -from.Z());
}

Ray3D Camera::CastRay(int x, int y) const
{
	auto xoffset = (x + 0.5) * _pixelSize;
	auto yoffset = (y + 0.5) * _pixelSize;

	auto world_x = half_w - xoffset;
	auto world_y = half_h - yoffset;

	auto inverse = Transformation.Inverse();
	auto pixel = inverse * Point3D(world_x, world_y, -1);
	auto origin = inverse * Point3D(0, 0, 0);
	auto direction = Vector3D::Normalize(pixel - origin);

	return Ray3D(origin, direction);
}

void Camera::Render(const Scene3D& scene, Canvas& canvas) const
{
	for (int y = 0; y < VSize; y++)
	{
		for (int x = 0; x < HSize; x++)
		{
			auto ray = CastRay(x, y);
			auto color = scene.ColorAt(ray);

			canvas.DrawPoint(x, y, color);
		}
		canvas.Update();
	}
}