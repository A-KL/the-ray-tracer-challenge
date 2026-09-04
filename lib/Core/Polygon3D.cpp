#include "Polygon3D.h"

const Point3D& Polygon3D::GetVertex(const int index) const
{
  assert(index <= vertices.size());
  return vertices[(index-1)];
}

const Vector3D& Polygon3D::GetNormal(const int index) const
{
  assert(index <= normals.size());
  return normals[(index-1)];
}

const TriangleShape3D* Polygon3D::GetTriangle(const int index) const
{
  assert(index <= all_triangles.size());
  return all_triangles[(index-1)];
}

const Group3D* Polygon3D::GetGroup(const int index) const
{
  assert(index <= groups.size());

  return &groups[(index-1)];
}

void Polygon3D::AddVertex(double p1, double p2, double p3)
{
  vertices.push_back(Point3D(p1, p2, p3));
}

void Polygon3D::AddNormal(double p1, double p2, double p3)
{
  normals.push_back(Vector3D(p1, p2, p3));
}

void Polygon3D::AddGroup(const char* name)
{
  Group3D default_group;

  groups.push_back(default_group);

  default_group_index++;
}

void Polygon3D::AddFaceWithIndex(
  int index_a, int index_b, int index_c,
  std::vector<int>& face_indexes, 
  std::vector<int>& normal_indexes)
{
  if (normal_indexes.empty()) 
  {
    triangles.emplace_back(
      vertices[(face_indexes[index_a]-1)], // X
      vertices[(face_indexes[index_b]-1)], // Y
      vertices[(face_indexes[index_c]-1)]  // Z
    );
    all_triangles.emplace_back(&triangles.back());  
  }
  else
  {                
    smooth_triangles.emplace_back(
      vertices[(face_indexes[index_a]-1)], // X
      vertices[(face_indexes[index_b]-1)], // Y
      vertices[(face_indexes[index_c]-1)], // Z

      normals[(normal_indexes[index_a]-1)], // NX
      normals[(normal_indexes[index_b]-1)], // NY
      normals[(normal_indexes[index_c]-1)]  // NZ
    );
    all_triangles.emplace_back(&smooth_triangles.back());  
  }
  groups[default_group_index].AddShape(all_triangles.back());
}

void Polygon3D::AddFace(std::vector<int>& face_indexes, std::vector<int>& normal_indexes)
{
  auto count = face_indexes.size();

  assert(count > 2);

  if (default_group_index < 0) 
  {
    AddGroup("default");
  }

  if (count == 3) 
  {
    AddFaceWithIndex(0, 1, 2, face_indexes, normal_indexes);
    return;
  }

  for (auto i = 1; i < count - 1; i++) 
  {
    AddFaceWithIndex(0, i, i+1, face_indexes, normal_indexes);
  }
}

int Polygon3D::GroupsCount()
{
  return groups.size();
}