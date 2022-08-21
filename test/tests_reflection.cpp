#include <iostream>
#include <list>

#include <vector>
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

#include "../lib/Core/Shape3D.h"
#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Plane3D.hpp"
#include "../lib/Core/Light3D.h"

#include "../lib/Core/Intersection.h"
#include "../lib/Core/Ray3D.h"
#include "../lib/Core/RayTracer.h"
#include "../lib/Core/Computation.h"

#include "tests.h"

void test_precomoute_reflection_vector()
{
	// Set up
	Plane3D sphere;
	Ray3D ray(Point3D(0, 1, -1), Vector3D(0, -sqrt(2)/2.0, sqrt(2)/2.0));
	Intersection interception(sqrt(2), sphere);

	// Act
	auto result = Computation::Prepare(interception, ray);

	// Assert
	assert(Vector3D(0.0, sqrt(2) / 2.0, sqrt(2) / 2.0) == result.Reflection);
}

void run_reflection_tests()
{
	test_precomoute_reflection_vector();
}