#include <list>
#include <cassert>

#include <sstream>
#include <iostream>

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

#include "tests.h"

std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void obj_load_polygon(const char* data, Polygon3D& result)
{
  std::istringstream f(data);
  std::string line;

  while (std::getline(f, line)) {
    ltrim(line);

    if (line.empty()) {
      continue;
    }

    auto tokens = split(line, " ");

    if (tokens[0] == "v") {
      result.AddVertex(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
    } 
    else if (tokens[0] == "f") {
      std::vector<int> face_indexes;

      for (auto i=1; i<tokens.size(); i++) {
        face_indexes.push_back(std::stoi(tokens[i]));
      }
     
      result.AddFace(face_indexes);
    }
    else if (tokens[0] == "g") {
        result.AddGroup(tokens[1].c_str());
    }
  }
}

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
  obj_load_polygon(data, polygon);

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
  obj_load_polygon(data, polygon);

  auto t1 = polygon.GetTriangle(1);
  auto t2 = polygon.GetTriangle(2);

  // Assert
  assert (polygon.GetVertex(1) == Point3D(-1, 1, 0));
  assert (polygon.GetVertex(2) == Point3D(-1, 0, 0));
  assert (polygon.GetVertex(3) == Point3D(1, 0, 0));
  assert (polygon.GetVertex(4) == Point3D(1, 1, 0));

  assert (t1.P1 == polygon.GetVertex(1));
  assert (t1.P2 == polygon.GetVertex(2));
  assert (t1.P3 == polygon.GetVertex(3));

  assert (t2.P1 == polygon.GetVertex(1));
  assert (t2.P2 == polygon.GetVertex(3));
  assert (t2.P3 == polygon.GetVertex(4));
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
  obj_load_polygon(data, polygon);

  auto t1 = polygon.GetTriangle(1);
  auto t2 = polygon.GetTriangle(2);
  auto t3 = polygon.GetTriangle(3);

  // Assert
  assert (t1.P1 == polygon.GetVertex(1));
  assert (t1.P2 == polygon.GetVertex(2));
  assert (t1.P3 == polygon.GetVertex(3));

  assert (t2.P1 == polygon.GetVertex(1));
  assert (t2.P2 == polygon.GetVertex(3));
  assert (t2.P3 == polygon.GetVertex(4));

  assert (t3.P1 == polygon.GetVertex(1));
  assert (t3.P2 == polygon.GetVertex(4));
  assert (t3.P3 == polygon.GetVertex(5));
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
  obj_load_polygon(data, polygon);

  auto g1 = polygon.GetGroup(1);
  auto g2 = polygon.GetGroup(2);

  auto t1 = dynamic_cast<const RefTriangle3D*>(g1->GetShape(0));
  auto t2 = dynamic_cast<const RefTriangle3D*>(g2->GetShape(0));

  // // Assert
  assert(2 == polygon.GroupsCount());

  assert (t1->P1 == polygon.GetVertex(1));
  assert (t1->P2 == polygon.GetVertex(2));
  assert (t1->P3 == polygon.GetVertex(3));

  assert (t2->P1 == polygon.GetVertex(1));
  assert (t2->P2 == polygon.GetVertex(3));
  assert (t2->P3 == polygon.GetVertex(4));
}

void run_obj_tests()
{
	test_parser_loads_vertex_data();

  test_parser_loads_vertex_and_face_data();

  test_parser_triangulates();

  test_obj_groups();
}