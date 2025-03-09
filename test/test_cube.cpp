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
#include "../lib/Core/Cube3D.hpp"

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"

void test_cube_ray_hit()
{
    // Setup
    Cube3D cube;
    Ray3D ray(Point3D(5, 0.5, 0), Vector3D(-1, 0, 0));

    // Act
    auto xs = cube.LocalIntersect(ray);
    
    //Assert
    assert(2 == xs.size());

    auto first = xs.begin();
    assert(4 == (first++)->Value);
    assert(6 == first->Value);
}

void test_cube_ray_miss()
{
    // Setup
    Cube3D cube;
    Ray3D ray(Point3D(-2, 0, 0), Vector3D(0.2673, 0.5343, 0.8018));

    // Act
    auto xs = cube.Intersect(ray);
    
    //Assert
    assert(xs.size() == 0);
}

void test_cube_normal()
{
    // Setup
    Cube3D cube;
    Point3D point(1, 0.5, -0.8);

    // Act
    auto normal = cube.NormalAt(point);
    
    //Assert
    assert(normal == Vector3D(1, 0, 0));
}

void run_cube_tests()
{
	test_cube_ray_hit();

    test_cube_ray_miss();

    test_cube_normal();
}