#pragma once

#include <iostream>
#include <vector>

#include "Point3D.h"
#include "Group3D.hpp"
#include "Triangle3D.h"

class Polygon3D
{
	public:
		Polygon3D() : vertices({}), triangles({})
		{}

		const Point3D GetVertex(const int index) const;

		const Triangle3D GetTriangle(const int index) const;

		void AddVertex(Point3D vertex);

		void AddFace(std::vector<int>& indexes);

	private:
		std::vector<Point3D> vertices;

		std::vector<Triangle3D> triangles;

		// Group3D triangles;
};