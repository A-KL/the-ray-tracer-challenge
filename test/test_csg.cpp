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
    Sphere3D sphere;
    Cube3D cube;
    
    CSG csg_uni(UnionRule, &sphere, &cube);
    CSG csg_int(IntersectRule, &sphere, &cube);
    CSG csg_dif(DifferenceRule, &sphere, &cube);

    auto xs = std::vector<Intersection> { 
      Intersection(1.0, &sphere),
      Intersection(2.0, &cube),
      Intersection(3.0, &sphere),
      Intersection(4.0, &cube)
     };

    // Act
    auto results_union = csg_uni.FilterIntersections(xs);
    auto results_intersection = csg_int.FilterIntersections(xs);
    auto results_difference = csg_dif.FilterIntersections(xs);
    
    //Assert
    assert(2 == results_union.size());
    assert(xs[0] == results_union[0]);
    assert(xs[3] == results_union[1]);

    assert(2 == results_intersection.size());
    assert(xs[1] == results_intersection[0]);
    assert(xs[2] == results_intersection[1]);

    assert(2 == results_difference.size());
    assert(xs[0] == results_difference[0]);
    assert(xs[1] == results_difference[1]);
}

// Tests #6: Intersecting a Ray with a CSG Object
//
// A ray should intersect a CSG object if it intersects any of its children.
//
void test_csg_ray_misses()
{
    // Setup
    Cube3D cube;
    Sphere3D sphere;

    CSG csg(UnionRule, &sphere, &cube); //<UnionRule>

    auto ray = Ray3D(Point3D(0, 2, -5), Vector3D(0, 0, 1));

    // Act
    auto xs = csg.LocalIntersect(ray);
    
    //Assert
    assert(0 == xs.size());
}

// Tests #7: Intersecting a Ray with a CSG Object
//
// A ray should intersect a CSG object if it intersects any of its children.
//
void test_csg_ray_hits()
{
    // Setup
    Sphere3D s1;
    Sphere3D s2(Matrix4d::Translate(0, 0, 0.5));

    CSG csg(UnionRule, &s1, &s2);

    auto ray = Ray3D(Point3D(0, 0, -5), Vector3D(0, 0, 1));

    // Act
    auto xs = csg.LocalIntersect(ray);

    //Assert
    assert(2   == xs.size());
    assert(4   == xs[0].Value);
    assert(&s1 == xs[0].Shape);
    assert(6.5 == xs[1].Value);
    assert(&s2 == xs[1].Shape);
}

void run_csg_tests()
{
  test_csg_filter();
  test_csg_ray_misses();
  test_csg_ray_hits();
}