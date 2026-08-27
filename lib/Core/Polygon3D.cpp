#include "Polygon3D.h"

const Point3D Polygon3D::GetVertex(const int index) const
{
  return vertices[(index-1)];
}

const Triangle3D Polygon3D::GetTriangle(const int index) const
{
  return triangles[(index-1)];
}

void Polygon3D::AddVertex(Point3D vertex)
{
  vertices.push_back(vertex);
}

void Polygon3D::AddFace(std::vector<int>& indexes)
{
  assert(indexes.size() > 2);

  // indexes.size() > 3
  //for (auto& i : indexes) {
    Triangle3D triangle(
      GetVertex(indexes[0]),  // X
      GetVertex(indexes[1]),  // Y
      GetVertex(indexes[2])); // Z

    triangles.push_back(triangle);
 // }
}