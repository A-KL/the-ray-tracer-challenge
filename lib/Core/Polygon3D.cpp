#include "Polygon3D.h"

const Point3D Polygon3D::GetVertex(const int index) const
{
  assert(index <= vertices.size());
  return vertices[(index-1)];
}

const RefTriangle3D& Polygon3D::GetTriangle(const int index) const
{
  assert(index <= triangles.size());
  return triangles[(index-1)];
}

const Group3D* Polygon3D::GetGroup(const int index) const
{
  assert(index <= groups.size());

  auto group = &groups[(index-1)];

  // std::cout << "GetGroup #" << index << " shapes count: " << (*group).ShapesCount() << std::endl;

  return group;
}

void Polygon3D::AddVertex(double p1, double p2, double p3)
{
  vertices.push_back(Point3D(p1, p2, p3));
}

void Polygon3D::AddGroup(const char* name)
{
  // std::cout << "AddGroup " << name << std::endl;

  Group3D default_group;

  groups.push_back(default_group);

  default_group_index++;
}

int Polygon3D::GroupsCount()
{
  return groups.size();
}

void Polygon3D::AddFace(std::vector<int>& indexes)
{
  auto count = indexes.size();

  assert(count > 2);

  if (default_group_index < 0) {
    AddGroup("default");
  }

  if (count == 3) 
  {
    triangles.emplace_back(
      vertices[(indexes[0]-1)], // X
      vertices[(indexes[1]-1)], // Y
      vertices[(indexes[2]-1)]  // Z
    );
    
    groups[default_group_index].AddShape(&triangles.back());

    // std::cout << "->> AddFace " << groups[default_group_index].ShapesCount() << std::endl;
  }
  else 
  {
    for (auto i = 1; i < count - 1; i++) {
      triangles.emplace_back(
        vertices[(indexes[0]-1)],      // X
        vertices[(indexes[i]-1)],      // Y
        vertices[(indexes[i + 1]-1)]   // Z
      );

      groups[default_group_index].AddShape(&triangles.back());

      // std::cout << "->> AddFace " << groups[default_group_index].ShapesCount() << std::endl;
    }
  }
}
