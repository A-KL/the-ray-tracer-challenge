#include <list>
#include <cassert>

#include "../lib/Mathf.h"
#include "../lib/Color3D.h"

#include "../lib/Primitive3D.h"
#include "../lib/Vector3D.h"
#include "../lib/Point3D.h"

#include "../lib/Matrix.hpp"
#include "../lib/MatrixOps.hpp"
#include "../lib/MatrixTransform.hpp"

#include "../lib/Color3D.h"
#include "../lib/Sphere3D.h"
#include "../lib/Light3D.h"
#include "../lib/World3D.h"

#include "tests.h"

void run_world_tests()
{
	// Setup
	World3D world;
	Light3D light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Sphere3D sphere1(Material(Color3D(0.8, 1.0, 0.6), 1, 0.7, 0.2));
	Sphere3D sphere2(Matrix4d::Scale(0.5, 0.5, 0.5));

	// Act
	world.Lights.push_back(light);
	world.Shapes.push_back(sphere1);
	world.Shapes.push_back(sphere2);

	// Assert
	assert(1 == world.Lights.size());
	assert(2 == world.Shapes.size());
}