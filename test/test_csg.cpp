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
#include "../lib/Core/Cube3D.h"
#include "../lib/Core/CSG.h"

#include "tests.h"

// Test #5: Filtering a List of Intersections
//
// Given a set of intersections, produce a subset of only those intersections that
// conform to the operation of the current CSG object.
//
void test_csg_filter()
{
    // Setup
    Cube3D cube;
    Sphere3D sphere;

    CSG csg(&sphere, &cube); //<UnionRule>

    auto xs = std::vector<Intersection> { 
      Intersection(1.0, &cube),
      Intersection(2.0, &sphere),
      Intersection(3.0, &cube),
      Intersection(4.0, &sphere)
     };

    // Act
    auto results = FilterIntersections(UnionRule, csg, xs);
    
    //Assert
    assert(2 == results.size());
    assert(xs[0] == results[0]);
    assert(xs[1] == results[1]);
}

// Tests #6 and 7: Intersecting a Ray with a CSG Object
//
// A ray should intersect a CSG object if it intersects any of its children.
//
void test_csg_ray_misses()
{
    // Setup
    Cube3D cube;
    Sphere3D sphere;

    CSG csg(&sphere, &cube); //<UnionRule>

    auto ray = Ray3D(Point3D(0, 2, -5), Vector3D(0, 0, 1));

    // Act
    auto xs = csg.LocalIntersect(ray);
    
    //Assert
    assert(0 == xs.size());
}

void run_csg_tests()
{
  test_csg_filter();
  test_csg_ray_misses();
}