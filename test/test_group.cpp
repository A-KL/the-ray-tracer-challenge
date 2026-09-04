#include <list>
#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/Canvas.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.h"
#include "../lib/Core/MatrixOps.h"
#include "../lib/Core/MatrixTransform.h"

#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Cylinder3D.h"
#include "../lib/Core/Group3D.h"

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"


// Tests #4: Intersecting a Ray with an empty Group
void test_ray_intersect_empty_group()
{
    // Setup
    Point3D origin(0, 0, 0);
    Vector3D direction(0, 0, 1);

    Group3D group;
    Ray3D ray(origin, direction);

    // Act
    auto xs = group.LocalIntersect(ray);
    
    //Assert
    assert(0 == xs.size());
}

// Tests #5: Intersecting a Ray with a full Group
void test_ray_intersect_full_group()
{
    // Setup
    Point3D origin(0, 0, -5);
    Vector3D direction(0, 0, 1);
    Ray3D ray(origin, direction);

    Group3D group;
    
    Sphere3D s1;
    Sphere3D s2(Matrix3d::Translate(0, 0, -3));
    Sphere3D s3(Matrix3d::Translate(5, 0, 0));

    group.AddShape(s1);
    group.AddShape(s2);
    group.AddShape(s3);

    // Act
    auto xs = group.LocalIntersect(ray);
    
    //Assert
    assert(4 == xs.size());

    assert(&s2 == xs[0].Shape);
    assert(&s2 == xs[1].Shape);
    assert(&s1 == xs[2].Shape);
    assert(&s1 == xs[3].Shape);
}

// Test #6: Group Transformations
// Demonstrate that group and child transformations are both applied.
void test_transformed_group()
{
    // Setup
    Ray3D ray(Point3D(10, 0, -10), Vector3D(0, 0, 1));

    Group3D group(Matrix3d::Scale(2, 2, 2));    
    Sphere3D s(Matrix3d::Translate(5, 0, 0));

    group.AddShape(s);

    // Act
    auto xs = group.Intersect(ray);

    //Assert
    assert(2 == xs.size());
}

Point3D WorldToObject(Shape3D& shape, const Point3D& point)
{
	auto object_point = point;

    if (shape.Parent != nullptr)
    {
        object_point = WorldToObject(*shape.Parent, object_point);
    }

    return (shape.Transformation.Inverse() * object_point);
}

Vector3D NormalToWorld(const Shape3D& shape, const Vector3D& normal)
{
    auto object_normal = shape.Transformation.Inverse().Transpose() * normal;
    object_normal.SetW(0);

    auto world_normal = object_normal.Normalize();

    if (shape.Parent != nullptr)
    {
        world_normal = NormalToWorld(*shape.Parent, world_normal);
    }

    return world_normal;
}

// Test #7: Convert a Point from World Space to Object Space
// 
// Take a point in world space and transform it to object space, taking into consideration any parent objects between the two spaces.
//
void test_convert_world_to_object_space()
{
    // Setup
    Group3D g1(Matrix3d::RotateY(M_PI / 2));
    Group3D g2(Matrix3d::Scale(2, 2, 2)); 

    Sphere3D s(Matrix3d::Translate(5, 0, 0));

    g1.AddShape(g2);
    g2.AddShape(s);
    
    Point3D p(-2, 0, -10);

    // Act
    auto result = WorldToObject(s, p);

    //Assert
    assert(Point3D(0, 0, -1) == result);
}

// Test #8: Convert a Normal Vector from Object Space to World Space
//
// Take a normal vector in object space and transform it to world space, taking
// into consideration any parent objects between the two spaces.
//
void test_convert_normal_to_world_space()
{
    // Setup
    Group3D g1(Matrix3d::RotateY(M_PI / 2));
    Group3D g2(Matrix3d::Scale(1, 2, 3)); 

    Sphere3D s(Matrix3d::Translate(5, 0, 0));

    g1.AddShape(g2);
    g2.AddShape(s);
    
    Vector3D n(0, 0, -1);

    // Act
    auto result = NormalToWorld(s, n); //TODO

    //Assert
    assert(Vector3D(0, 0, -1) == result);
}

// Test #9: Find the Normal on an Object in a Group
//
// Find the normal on a child object of a group, taking into account transformations
// on both the child object and the parent(s).
//
void test_normal_on_child_object()
{
    // Setup
    Group3D g1(Matrix3d::RotateY(M_PI / 2));
    Group3D g2(Matrix3d::Scale(1, 2, 3)); 

    Sphere3D s(Matrix3d::Translate(5, 0, 0));

    g1.AddShape(g2);
    g2.AddShape(s);

    Point3D p(1.7321, 1.1547, -5.5774);

    // Act
    auto result = s.NormalAt(p);
    
    //Assert
    assert(Vector3D(0.2857, 0.4286, -0.8571) == result);
}

void run_group_tests()
{
    test_ray_intersect_empty_group();

    test_ray_intersect_full_group();
    
    test_transformed_group();

    test_convert_world_to_object_space();

    test_convert_world_to_object_space();

    test_normal_on_child_object();
}