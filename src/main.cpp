#include <list>

#include <Arduino.h>
#include <M5GFX.h>

#include "Mathf.h"

#include "Color3D.h"
#include "Canvas.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Point3D.h"

#include "Matrix.hpp"
#include "MatrixOps.hpp"
#include "MatrixTransform.hpp"

#include "Environment.h"
#include "Projectile.h"

#include "Material3D.h"
#include "Object3D.h"

#include "Shape3D.h"
#include "Intersection.h"
#include "Sphere3D.h"
#include "Plane3D.hpp"
#include "Light3D.h"
#include "RayTracer.h"
#include "Scene3D.h"
#include "Camera.h"

#include "M5StackCanvas.h"

M5GFX display;
M5StackCanvas canvas(display);
//#include <M5UnitOLED.h>
//M5UnitOLED display; // default setting
//M5UnitOLED display ( 21, 22, 400000 ); // SDA, SCL, FREQ

//#include <M5UnitLCD.h>
//M5UnitLCD display;  // default setting
//M5UnitLCD display  ( 21, 22, 400000 ); // SDA, SCL, FREQ

void run_scene_demo(Canvas& canvas)
{
	const int w = canvas.Witdth(); //100
	const int h = canvas.Height(); //50

	auto left_wall_location = 
		Matrix4d::Translate(0, 0, 5) * 
		Matrix4d::RotateY(-M_PI/4) * Matrix4d::RotateX(M_PI/2) *
		Matrix4d::Scale(10, 0.01, 10);


	auto right_wall_location =
		Matrix4d::Translate(0, 0, 5) *
		Matrix4d::RotateY(M_PI / 4) * Matrix4d::RotateX(M_PI / 2) *
		Matrix4d::Scale(10, 0.01, 10);

	Material3D floor_material(1, 0.9, 0.9, 0.1, 0.9, 0);

	Sphere3D floor(Matrix4d::Scale(10, 0.01, 10), floor_material);
	Sphere3D left_wall(left_wall_location, floor_material);
	Sphere3D right_wall(right_wall_location, floor_material);

	// -----------------------------------------------------------------------------

	Sphere3D middle(Matrix4d::Translate(-0.5, 1, 0.5), Material3D(0.1, 1, 0.5, 0.1, 0.7, 0.3));

	Sphere3D right(Matrix4d::Translate(1.5, 0.5, -0.5) * Matrix4d::Scale(0.5), Material3D(0.5, 1, 0.1, 0.1, 0.7, 0.3));

	Sphere3D left(Matrix4d::Translate(-1.5, 0.33, -0.75) * Matrix4d::Scale(0.33), Material3D(1, 0.8, 0.1, 0.1, 0.7, 0.3));

	// -----------------------------------------------------------------------------

	Light3D main_light(Point3D(-10, 10, -10), Color3D(1, 1, 1));

	Camera main_camera(w, h, M_PI/3, Point3D(0, 1.5, -5), Point3D(0, 1, 0), Vector3D(0, 1, 0));

	// -----------------------------------------------------------------------------

	Scene3D scene;

	scene.Lights.push_back(&main_light);

	scene.Shapes.push_back(&floor);
	scene.Shapes.push_back(&left_wall);
	scene.Shapes.push_back(&right_wall);

	scene.Shapes.push_back(&middle);
	scene.Shapes.push_back(&right);
	scene.Shapes.push_back(&left);

	main_camera.Render(scene, canvas);
}

void setup(void)
{ 
    canvas.Init();
	display.waitDisplay();

	//run_gravity_demo(canvas);
	//run_clock_demo(canvas);
	//run_shadow_demo(canvas);
	//run_light_demo(canvas);

	run_scene_demo(canvas);
}

void loop(void)
{ 
  delay(10);
}
