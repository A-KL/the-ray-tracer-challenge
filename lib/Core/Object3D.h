#pragma once

class Object3D
{
public:
	Object3D(const Point3D& position);

	Object3D(const Point3D& position, const Matrix4d& transform);

	const Point3D Position;

	const Matrix4d Transformation;

	bool operator==(const Object3D& other) const;
};


