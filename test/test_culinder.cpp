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

// void test_cylinder3D_ray_hit()
// {
//     // Setup
//     Cube3D cube;
//     Ray3D ray(Point3D(5, 0.5, 0), Vector3D(-1, 0, 0));

//     // Act
//     auto xs = cube.LocalIntersect(ray);
    
//     //Assert
//     assert(2 == xs.size());

//     auto first = xs.begin();
//     assert(4 == (first++)->Value);
//     assert(6 == first->Value);
// }

void test_cylinder_ray_miss()
{
    // Setup
    Vector3D direction(1, 1, 1);
    Point3D origin(0, 0, -5);

    Cylinder3D cylinder;
    Ray3D ray(origin, direction);

    // Act
    auto xs = cylinder.LocalIntersect(ray);
    
    //Assert
    assert(xs.size() == 0);
}

// void test_cube_normal()
// {
//     // Setup
//     Cube3D cube;
//     Point3D point(1, 0.5, -0.8);

//     // Act
//     auto normal = cube.NormalAt(point);
    
//     //Assert
//     assert(normal == Vector3D(1, 0, 0));
// }

void run_cylinder_tests()
{
	test_cylinder_ray_miss();
}