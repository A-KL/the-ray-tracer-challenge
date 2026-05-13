#include <list>
#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/Canvas.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.hpp"
#include "../lib/Core/MatrixOps.hpp"
#include "../lib/Core/MatrixTransform.hpp"

#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Cylinder3D.hpp"
#include "../lib/Core/Group3D.hpp"

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"

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

void run_group_tests()
{
    test_ray_intersect_empty_group();

    test_ray_intersect_full_group();
}