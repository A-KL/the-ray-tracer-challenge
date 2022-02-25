#pragma once

class Object3D
{
public:
	Object3D(const Point3D& position) :
		Object3D(position, matrix_identity_4d)
	{ }

	Object3D(const Point3D& position, const Matrix4d& transform) :
		Position(position),
		Transformation(transform)
	{ }

	const Point3D Position;

	const Matrix4d Transformation;

	bool operator==(const Object3D& other) const;
};


