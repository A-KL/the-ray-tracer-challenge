#include <math.h>
#include "Mathf.h"
#include "Color3D.h"
#include "Material3D.h"

const Material3D Material3D::Default(Color3D::White);

Material3D::Material3D(const Material3D& material)
	: Material3D(material.Color, material.Ambient, material.Diffuse, material.Specular, material.Shininess)
{ }

Material3D::Material3D(double r, double g, double b, double ambient, double diffuse, double specular, double shininess)
	: Color(Color3D(r, g, b)), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{  }

Material3D::Material3D(const Color3D& color, double ambient, double diffuse, double specular, double shininess)
	: Color(color), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{  }


bool Material3D::operator==(const Material3D& other) const
{
	return
		Color == other.Color &&
		Mathf<double>::Approximately(Ambient, other.Ambient) &&
		Mathf<double>::Approximately(Diffuse, other.Diffuse) &&
		Mathf<double>::Approximately(Specular, other.Specular) &&
		Mathf<double>::Approximately(Shininess, other.Shininess);
}