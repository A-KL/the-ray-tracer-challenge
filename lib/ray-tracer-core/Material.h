#pragma once

class Material
{
public:
	Material(const Material& material)
		: Material(material.Color, material.Ambient, material.Diffuse, material.Specular, material.Shininess)
	{ }

	Material(const Color3D& color, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200)
		: Color(color), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
	{  }

	~Material()
	{}

	Color3D Color;

	double Ambient = 0.1;
	double Diffuse = 0.9;
	double Specular = 0.9;
	double Shininess = 200;
};

