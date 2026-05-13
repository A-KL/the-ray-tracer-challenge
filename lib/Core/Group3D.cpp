#include <math.h>

#include "Mathf.h"
#include "Group3D.hpp"

Group3D::Group3D() :
    Group3D(Matrix4d::Identity())
{ }

Group3D::Group3D(const Matrix4d& transform) :
    Group3D(Point3D::Origin, transform)
{ }

Group3D::Group3D(const Point3D& position, const Matrix4d& transform) :
	Shape3D(position, transform, Material3D::Default)
{ }

Group3D* Group3D::AddShape(Shape3D& shape) 
{
    return AddShape((Shape3D*)&shape);
}

Group3D* Group3D::AddShape(Shape3D* shape) 
{
    shape->Parent = this;
    _shapes.push_back(shape);
    return this;
}

bool Group3D::operator==(const Group3D& other) const 
{
    return ((Object3D)*this) == other && _shapes == other._shapes;
}

std::vector<Intersection> Group3D::LocalIntersect(const Ray3D& ray) const
{
    std::list<Intersection> results;

    for (auto shape : _shapes)
    {
        auto xs = shape->Intersect(ray);
        results.insert(results.end(), xs.begin(), xs.end());
    }

    results.sort([](const Intersection& a, const Intersection& b) {
        return a.Value < b.Value;
    });

    return std::vector<Intersection>(results.begin(), results.end());
}

const Vector3D Group3D::LocalNormalAt(const Point3D& point) const
{
    throw std::logic_error("Group3D does not implement LocalNormalAt");
}