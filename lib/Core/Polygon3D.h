#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "Point3D.h"
#include "Group3D.hpp"
#include "Triangle3D.h"

class Polygon3D
{
	public:
		Polygon3D() : vertices({}), normals({}), triangles({}), groups({})
		{}

		const Point3D& GetVertex(const int index) const;

		const RefTriangle3D& GetTriangle(const int index) const;

		const Group3D* GetGroup(const int index) const;

		const Vector3D& GetNormal(const int index) const;


		void AddVertex(double p1, double p2, double p3);

		void AddNormal(double p1, double p2, double p3);

		void AddFace(std::vector<int>& indexes);

		void AddGroup(const char* name);


		int GroupsCount();

	private:
		std::deque<Point3D> vertices;

		std::deque<Vector3D> normals;

		std::deque<RefTriangle3D> triangles;

		std::deque<Group3D> groups;

		int default_group_index = -1;
};
