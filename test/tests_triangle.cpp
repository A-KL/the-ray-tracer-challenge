#include <list>
#include <cassert>

#include "../lib/Core/Mathf.h"
#include "../lib/Core/Color3D.h"

#include "../lib/Core/Primitive3D.h"
#include "../lib/Core/Vector3D.h"
#include "../lib/Core/Point3D.h"

#include "../lib/Core/Matrix.hpp"
#include "../lib/Core/MatrixOps.hpp"
#include "../lib/Core/MatrixTransform.hpp"

#include "../lib/Core/Material3D.h"

#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Triangle3D.h"
#include "../lib/Core/Light3D.h"

#include "../lib/Core/Intersection.h"
#include "../lib/Core/Ray3D.h"
#include "../lib/Core/Computation.h"
#include "../lib/Core/RayTracer.h"

#include "../lib/Core/Scene3D.h"

#include "tests.h"

// Test #2: Normal Vector for a Triangle
//
// The triangle s precomputed normal is used for every point on the triangle.
//
void test_finding_normal()
{
  // Set up
  Triangle3D triangle(Point3D(0, 1, 0), Point3D(-1, 0, 0), Point3D(1, 0, 0));

  // Act
  auto n1 = triangle.NormalAt(Point3D(0, 0.5, 0));
  auto n2 = triangle.NormalAt(Point3D(-0.5, 0.75, 0));
  auto n3 = triangle.NormalAt(Point3D(0.5, 0.25, 0));

  // Assert
  assert(triangle.Normal == n1);
  assert(triangle.Normal == n2);
  assert(triangle.Normal == n3);
}

// Tests #3: Intersecting a Ray with a Triangle
//
// Intersecting a ray parallel to the triangle
//
void test_intersect_parallel_ray()
{
  // Set up
  Triangle3D triangle(Point3D(0, 1, 0), Point3D(-1, 0, 0), Point3D(1, 0, 0));
  Ray3D ray(Point3D(0, -1, -2), Vector3D(0, 1, 0));

  // Act
  auto xs = triangle.LocalIntersect(ray);

  // Assert
  assert(true == xs.empty());
}

// Tests #4: Intersecting a Ray with a Triangle
//
// A ray misses the p1-p3 edge
//
void test_ray_misses_p1_p3()
{
  // Set up
  Triangle3D triangle(Point3D(0, 1, 0), Point3D(-1, 0, 0), Point3D(1, 0, 0));
  Ray3D ray(Point3D(1, 1, -2), Vector3D(0, 0, 1));

  // Act
  auto xs = triangle.LocalIntersect(ray);
  
  // Assert
  assert(true == xs.empty());
}

void run_triangle_tests()
{
	test_finding_normal();

  test_intersect_parallel_ray();

  test_ray_misses_p1_p3();
}