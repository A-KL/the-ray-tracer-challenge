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

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"

void test_cylinder_ray_hit()
{
    // Setup
    Point3D origin(0.5, 0, -5);
    Vector3D direction(0.1, 1, 1);

    Cylinder3D cube;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cube.LocalIntersect(ray);
    
    //Assert
    auto first = xs.begin();
    auto t0 = (first++)->Value;
    auto t1 = first->Value;

    assert(2 == xs.size());
    assert(Mathf<double>::Approximately(6.80798, t0));
    assert(Mathf<double>::Approximately(7.08872, t1));
}

void test_cylinder_ray_miss()
{
    // Setup
    Vector3D direction(1, 1, 1);
    Point3D origin(0, 0, -5);

    Cylinder3D cylinder;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cylinder.LocalIntersect(ray);
    
    //Assert
    assert(xs.size() == 0);
}

void test_cylinder_normal()
{
    // Setup
    Cylinder3D cube;
    Point3D point(-1, 1, 0);

    // Act
    auto normal = cube.NormalAt(point);
    
    //Assert
    assert(normal == Vector3D(-1, 0, 0));
}

void test_cylinder_constrains()
{
    // Setup
    Vector3D direction(0, 1, -5);
    Point3D origin(0, 0, 1);

    Cylinder3D cylinder;
    cylinder.Min = 1;
    cylinder.Max = 2;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cylinder.LocalIntersect(ray);
    
    //Assert
    assert(0 == xs.size());
}

void run_cylinder_tests()
{
	test_cylinder_ray_miss();

    test_cylinder_ray_hit();

    test_cylinder_normal();

    test_cylinder_constrains();
}