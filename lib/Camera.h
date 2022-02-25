#pragma once

struct Camera
{
	Camera(int h, int v, double fow, const Matrix4d& transformation);

	Camera(int h, int v, double fow, const Point3D& from, const Point3D& to, const Vector3D& up);

	Ray3D CastRay(int x, int y) const;

	void Render(const Scene3D& scene, Canvas& canvas) const;

	static Matrix4d ViewTransform(const Point3D& from, const Point3D& to, const Vector3D& up);

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