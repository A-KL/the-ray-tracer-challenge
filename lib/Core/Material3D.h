#pragma once

struct Material3D
{
	Material3D(const Material3D& material)
		: Material3D(material.Color, material.Ambient, material.Diffuse, material.Specular, material.Shininess)
	{ }

	Material3D(double r = 1, double g = 1, double b = 1, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200)
		: Color(Color3D(r, g, b)), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
	{  }

	Material3D(const Color3D& color, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200)
		: Color(color), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
	{  }

	~Material3D()
	{}

	bool operator==(const Material3D& other) const;

	const Color3D Color;

	const double Ambient = 0.1;
	const double Diffuse = 0.9;
	const double Specular = 0.9;
	const double Shininess = 200;

	const static Material3D Default;
};

