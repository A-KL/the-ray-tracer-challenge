#pragma once

class Material
{
public:
	Material(const Material& material)
		: Material(material.ambient, material.ambient, material.ambient)
	{ }

	Material(double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200)
		: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
	{  }

	~Material()
	{}

	unsigned int color;

	double ambient = 0.1;
	double diffuse = 0.9;
	double specular = 0.9;
	double shininess = 200;
};

