#pragma once

#include <math.h>

struct Camera
{
	Camera(int h, int v, double fow, const Matrix4d& transformation) :
		HSize(h), VSize(v), FieldOfView(fow), Transformation(transformation)
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

	Ray3D CastRay(int x, int y) const
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

	const int HSize;

	const int VSize;

	const Matrix4d Transformation;

	const double FieldOfView;

	inline double PixelSize()
	{
		return _pixelSize;
	}

private :
	double _pixelSize, half_w, half_h;
};