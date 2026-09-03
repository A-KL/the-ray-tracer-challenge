#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "Point3D.h"
#include "Group3D.h"
#include "Triangle3D.h"

class Polygon3D
{
	public:
		Polygon3D() : vertices({}), normals({}), smooth_triangles({}), triangles({}), all_triangles({}), groups({})
		{}

		const Point3D& GetVertex(const int index) const;

		const Vector3D& GetNormal(const int index) const;

		const TriangleShape3D* GetTriangle(const int index) const;

		const Group3D* GetGroup(const int index) const;

		void AddVertex(double p1, double p2, double p3);

		void AddNormal(double p1, double p2, double p3);

		void AddFace(std::vector<int>& face_indexes, std::vector<int>& normal_indexes);

		void AddGroup(const char* name);

		int GroupsCount();

	private:
		std::deque<Point3D> vertices;

		std::deque<Vector3D> normals;

		std::deque<SmoothTriangle3D> smooth_triangles;

		std::deque<Triangle3D> triangles;

		std::deque<TriangleShape3D*> all_triangles;

		std::deque<Group3D> groups;

		int default_group_index = -1;

		void AddFaceWithIndex(
			int index_a, int index_b, int index_c,
			std::vector<int>& face_indexes, 
			std::vector<int>& normal_indexes);
};
