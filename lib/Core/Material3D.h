#pragma once

#include "ColorPattern.h"

struct Material3D
{
	Material3D(const Material3D& material);

	Material3D(const ColorPattern& pattern, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0, double refractive_index = 1.0);

	Material3D(const ColorPattern* pattern, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0, double refractive_index = 1.0);

	bool operator==(const Material3D& other) const;

	const ColorPattern* Pattern;

	const double Ambient;
	const double Diffuse;
	const double Specular;
	const double Shininess;
	const double Reflective;
	const double Transparency;
	const double RefractiveIndex;

	const static Material3D Default;
};
