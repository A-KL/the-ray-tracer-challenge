#pragma once


class Material
{
public:
	Material(const Material& material)
		: Material(material.Color, material.ambient, material.ambient, material.ambient)
	{ }

	Material(const Color& color, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200)
		: Color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
	{  }

	~Material()
	{}

	const Color Color;

	double ambient = 0.1;
	double diffuse = 0.9;
	double specular = 0.9;
	double shininess = 200;
};

