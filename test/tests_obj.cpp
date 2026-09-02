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
#include "../lib/Core/Polygon3D.h"

#include "../lib/Utils/ObjLoader.hpp"

#include "tests.h"


// Test #9: OBJ File with Vertex Data
//
// The parser should process vertex data from the given input.
//
void test_parser_loads_vertex_data()
{
  // Arrange
  const char* data = "\
    v -1 1 0\n\
    v -1.0000 0.5000 0.0000\n\
    v 1 0 0\n\
    v 1 1 0";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  // Assert
  assert (polygon.GetVertex(1) == Point3D(-1, 1, 0));
  assert (polygon.GetVertex(2) == Point3D(-1, 0.5, 0));
  assert (polygon.GetVertex(3) == Point3D(1, 0, 0));
  assert (polygon.GetVertex(4) == Point3D(1, 1, 0));
}

// Test #10: OBJ File with Triangle Data
//
// The parser should process triangle data from the given input.
//
void test_parser_loads_vertex_and_face_data()
{
  // Arrange
  const char* data = "\
    v -1 1 0\n\
    v -1 0 0\n\
    v 1 0 0\n\
    v 1 1 0\n\
    \
    f 1 2 3\n\
    f 1 3 4";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  auto t1 = polygon.GetTriangle(1);
  auto t2 = polygon.GetTriangle(2);

  // Assert
  assert (polygon.GetVertex(1) == Point3D(-1, 1, 0));
  assert (polygon.GetVertex(2) == Point3D(-1, 0, 0));
  assert (polygon.GetVertex(3) == Point3D(1, 0, 0));
  assert (polygon.GetVertex(4) == Point3D(1, 1, 0));

  assert (t1->P1 == polygon.GetVertex(1));
  assert (t1->P2 == polygon.GetVertex(2));
  assert (t1->P3 == polygon.GetVertex(3));

  assert (t2->P1 == polygon.GetVertex(1));
  assert (t2->P2 == polygon.GetVertex(3));
  assert (t2->P3 == polygon.GetVertex(4));
}

// Test #11:  OBJ File with Polygon Data
//
// The parser should process and triangulate polygonal data from the given input.
//
void test_parser_triangulates()
{
  // Arrange
  const char* data = "\
    v -1 1 0\n\
    v -1 0 0\n\
    v 1 0 0\n\
    v 1 1 0\n\
    v 0 2 0\n\
    \
    f 1 2 3 4 5";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  auto t1 = polygon.GetTriangle(1);
  auto t2 = polygon.GetTriangle(2);
  auto t3 = polygon.GetTriangle(3);

  // Assert
  assert (t1->P1 == polygon.GetVertex(1));
  assert (t1->P2 == polygon.GetVertex(2));
  assert (t1->P3 == polygon.GetVertex(3));

  assert (t2->P1 == polygon.GetVertex(1));
  assert (t2->P2 == polygon.GetVertex(3));
  assert (t2->P3 == polygon.GetVertex(4));

  assert (t3->P1 == polygon.GetVertex(1));
  assert (t3->P2 == polygon.GetVertex(4));
  assert (t3->P3 == polygon.GetVertex(5));
}

// Test #12: Named Groups in OBJ Files
//
// The parser should recognize a group statement and add subsequent triangles to the named group.
//
void test_obj_groups()
{
    // Arrange
  const char* data = "\
    v -1 1 0\n\
    v -1 0 0\n\
    v 1 0 0\n\
    v 1 1 0\n\
    g FirstGroup\n\
    f 1 2 3\n\
    g SecondGroup\n\
    f 1 3 4";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  auto g1 = polygon.GetGroup(1);
  auto g2 = polygon.GetGroup(2);

  auto t1 = dynamic_cast<const Triangle3D*>(g1.GetShape(0));
  auto t2 = dynamic_cast<const Triangle3D*>(g2.GetShape(0));

  // // Assert
  assert(2 == polygon.GroupsCount());

  assert (t1->P1 == polygon.GetVertex(1));
  assert (t1->P2 == polygon.GetVertex(2));
  assert (t1->P3 == polygon.GetVertex(3));

  assert (t2->P1 == polygon.GetVertex(1));
  assert (t2->P2 == polygon.GetVertex(3));
  assert (t2->P3 == polygon.GetVertex(4));
}

// Test #16: Populate u and v on Triangle Intersections
//
// When intersecting triangles, preserve the u and v values in the resulting inter-section.
//
void test_obj_interception_with_u_and_v()
{
  // Arrange
  auto t = Triangle3D(
    Point3D(0, 1, 0), Point3D(-1, 0, 0), Point3D(1, 0, 0));

  auto ray = Ray3D(
    Point3D(-0.2, 0.3, -2), Vector3D(0, 0, 1));

  // Act
  auto xs = t.LocalIntersect(ray);

  // Assert
  assert(1 == xs.size());
  assert(Mathf<double>::Approximately(0.45, xs[0].U));
  assert(Mathf<double>::Approximately(0.25, xs[0].V));
}

// Test #19: OBJ File with Vertex Normal Data
//
// Vertex normal data should be correctly imported from an OBJ file.
//
void test_obj_data_with_vertex_normals()
{
  // Arrange
  const char* data = "\
    v 0 1 0\n\
    v -1 0 0\n\
    v 1 0 0\n\
    vn -1 0 0\n\
    vn 1 0 0\n\
    vn 0 1 0";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  // Assert
  assert(Vector3D(-1, 0, 0) == polygon.GetNormal(1));
  assert(Vector3D(1, 0, 0) == polygon.GetNormal(2));
  assert(Vector3D(0, 1, 0) == polygon.GetNormal(3));
}

// Test #20: Faces with Normal Vectors
//
//Vertex normal data should be correctly associated with face data from an OBJ file.
//
void test_obj_faces_with_vertex_normals()
{
  // Arrange
  const char* data = "\
    v 0 1 0\n\
    v -1 0 0\n\
    v 1 0 0\n\
    \n\
    vn -1 0 0\n\
    vn 1 0 0\n\
    vn 0 1 0\n\
    \n\
    f 1//3 2//1 3//2\n\
    f 1/0/3 2/102/1 3/14/2";

  Polygon3D polygon;

  // Act
  obj_load_from_string(data, polygon);

  auto g1 = polygon.GetGroup(1);

  auto t1 = dynamic_cast<const Triangle3D*>(g1.GetShape(0));
  auto t2 = dynamic_cast<const Triangle3D*>(g1.GetShape(1));

  // Assert
  assert (t1->P1 == polygon.GetVertex(1));
  assert (t1->P2 == polygon.GetVertex(2));
  assert (t1->P3 == polygon.GetVertex(3));

  // assert (t1->N1 == polygon.GetNormal(3));
  // assert (t1->N2 == polygon.GetNormal(1));
  // assert (t1->N3 == polygon.GetNormal(2));
  
  assert(*t2 == *t1);
}

void run_obj_tests()
{
	test_parser_loads_vertex_data();

  test_parser_loads_vertex_and_face_data();

  test_parser_triangulates();

  test_obj_interception_with_u_and_v();

  test_obj_groups();

  test_obj_data_with_vertex_normals();

  test_obj_faces_with_vertex_normals();
}