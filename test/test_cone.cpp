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
#include "../lib/Core/Cone3D.h"

#include "../lib/Core/Camera.h"
#include "../lib/Core/InMemoryCanvas.h"

#include "tests.h"

void test_cone_ray_hit()
{
    // Setup
    Point3D origin(0, 0, -5);
    Vector3D direction(0, 0, 1);

    Cone3D cone;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cone.LocalIntersect(ray);
    
    //Assert
    auto first = xs.begin();
    auto t0 = (first++)->Value;
    auto t1 = first->Value;

    assert(2 == xs.size());
    assert(Mathf<double>::Approximately(5, t0));
    assert(Mathf<double>::Approximately(5, t1));
}

void test_cone_ray_hit_v2()
{
    // Setup
    Point3D origin(0, 0, -5);
    Vector3D direction(1, 1, 1);

    Cone3D cone;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cone.LocalIntersect(ray);
    
    //Assert
    auto first = xs.begin();
    auto t0 = (first++)->Value;
    auto t1 = first->Value;

    assert(2 == xs.size());
    assert(Mathf<double>::Approximately(8.66025, t0));
    assert(Mathf<double>::Approximately(8.66025, t1));
}

void test_cone_ray_parallel_to_halfs()
{
    // Setup
    Point3D origin(0, 0, -1);
    Vector3D direction(0, 1, 1);

    Cone3D cone;
    Ray3D ray(origin, direction.Normalize());

    // Act
    auto xs = cone.LocalIntersect(ray);
    
    //Assert
    auto first = xs.begin();
    auto t0 = (first++)->Value;

    assert(1 == xs.size());
    assert(Mathf<double>::Approximately(0.35355, t0));
}

void test_cone_normal_vector()
{
    // Setup
    Point3D origin(1, 1, 1);
    Vector3D direction(1, -std::sqrt(2), 1);

    Cone3D cone;

    // Act
    auto normal = cone.LocalNormalAt(origin);
    
    //Assert
    assert(normal == direction);
}

void run_cone_tests()
{
	test_cone_ray_hit();
	test_cone_ray_hit_v2();
    test_cone_ray_parallel_to_halfs();
    test_cone_normal_vector();
}