#include <iostream>
#include "../lib/Core/Color3D.h"
#include "../lib/Core/Scene3D.h"
#include "../lib/Core/Canvas.h"
#include "../lib/Core/Camera.h"
#include "../lib/Core/Color3D.h"
#include "../lib/Core/Light3D.h"
#include "../lib/Core/Material3D.h"
#include "../lib/Core/Matrix.h"
#include "../lib/Core/MatrixOps.h"
#include "../lib/Core/MatrixTransform.h"
#include "../lib/Core/Plane3D.h"
#include "../lib/Core/Sphere3D.h"
#include "../lib/Core/Cube3D.h"

void run_cover_demo(Canvas& canvas) {

    const int w = canvas.Width();
    const int h = canvas.Height();

    Scene3D scene;

    auto camera = 
       Camera(100, 100, 0.785, Point3D(-6, 6, -10), Point3D(6, 0, 6), Vector3D(-0.45, 1, 0));

    auto light = 
       Light3D(Point3D(50, 100, -50), Color3D(1, 1, 1));

    scene.Lights.push_back(&light);

    auto light2 = 
       Light3D(Point3D(-400, 50, -10), Color3D(0.2, 0.2, 0.2));

    scene.Lights.push_back(&light2);

    auto white_material = 
       Material3D(SolidColor3D(Color3D(1, 1, 1)), 0.1, 0.7, 0.0, 200, 0.1, 0.0);

    auto blue_material = 
       Material3D(SolidColor3D(Color3D(0.537, 0.831, 0.914)), 0.1, 0.7, 0.0, 200, 0.1, 0.0);

    auto red_material = 
       Material3D(SolidColor3D(Color3D(0.941, 0.322, 0.388)), 0.1, 0.7, 0.0, 200, 0.1, 0.0);

    auto purple_material = 
       Material3D(SolidColor3D(Color3D(0.373, 0.404, 0.55)), 0.1, 0.7, 0.0, 200, 0.1, 0.0);

    auto standard_transform = 
       Matrix4d::Translate(1, -1, 1) *
       Matrix4d::Scale(0.5, 0.5, 0.5);

    auto large_object = 
       standard_transform *
       Matrix4d::Scale(3.5, 3.5, 3.5);

    auto medium_object = 
       standard_transform *
       Matrix4d::Scale(3, 3, 3);

    auto small_object = 
       standard_transform *
       Matrix4d::Scale(2, 2, 2);

    auto plane = Plane3D(
         Matrix4d::RotateX(1.5707963267948966) *Matrix4d::Translate(0, 0, 500),
         Material3D(SolidColor3D(Color3D(1, 1, 1)), 1, 0, 0, 200, 0.0, 0.0));

    scene.Shapes.push_back(&plane);

    auto sphere = Sphere3D(
         large_object,
         Material3D(SolidColor3D(Color3D(0.373, 0.404, 0.55)), 0.0, 0.2, 1.0, 200, 0.7, 0.7));

    scene.Shapes.push_back(&sphere);

    auto cube = Cube3D(
         medium_object * Matrix4d::Translate(4, 0, 0),
         white_material);

    scene.Shapes.push_back(&cube);

    auto cube2 = Cube3D(
         large_object * Matrix4d::Translate(8.5, 1.5, -0.5),
         blue_material);

    scene.Shapes.push_back(&cube2);

    auto cube3 = Cube3D(
         large_object * Matrix4d::Translate(0, 0, 4),
         red_material);

    scene.Shapes.push_back(&cube3);

    auto cube4 = Cube3D(
         small_object * Matrix4d::Translate(4, 0, 4),
         white_material);

    scene.Shapes.push_back(&cube4);

    auto cube5 = Cube3D(
         medium_object * Matrix4d::Translate(7.5, 0.5, 4),
         purple_material);

    scene.Shapes.push_back(&cube5);

    auto cube6 = Cube3D(
         medium_object * Matrix4d::Translate(-0.25, 0.25, 8),
         white_material);

    scene.Shapes.push_back(&cube6);

    auto cube7 = Cube3D(
         large_object * Matrix4d::Translate(4, 1, 7.5),
         blue_material);

    scene.Shapes.push_back(&cube7);

    auto cube8 = Cube3D(
         medium_object * Matrix4d::Translate(10, 2, 7.5),
         red_material);

    scene.Shapes.push_back(&cube8);

    auto cube9 = Cube3D(
         small_object * Matrix4d::Translate(8, 2, 12),
         white_material);

    scene.Shapes.push_back(&cube9);

    auto cube10 = Cube3D(
         small_object * Matrix4d::Translate(20, 1, 9),
         white_material);

    scene.Shapes.push_back(&cube10);

    auto cube11 = Cube3D(
         large_object * Matrix4d::Translate(-0.5, -5, 0.25),
         blue_material);

    scene.Shapes.push_back(&cube11);

    auto cube12 = Cube3D(
         large_object * Matrix4d::Translate(4, -4, 0),
         red_material);

    scene.Shapes.push_back(&cube12);

    auto cube13 = Cube3D(
         large_object * Matrix4d::Translate(8.5, -4, 0),
         white_material);

    scene.Shapes.push_back(&cube13);

    auto cube14 = Cube3D(
         large_object * Matrix4d::Translate(0, -4, 4),
         white_material);

    scene.Shapes.push_back(&cube14);

    auto cube15 = Cube3D(
         large_object * Matrix4d::Translate(-0.5, -4.5, 8),
         purple_material);

    scene.Shapes.push_back(&cube15);

    auto cube16 = Cube3D(
         large_object * Matrix4d::Translate(0, -8, 4),
         white_material);

    scene.Shapes.push_back(&cube16);

    auto cube17 = Cube3D(
         large_object * Matrix4d::Translate(-0.5, -8.5, 8),
         white_material);

    scene.Shapes.push_back(&cube17);


    camera.Render(scene, canvas);
}
