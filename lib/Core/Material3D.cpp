#include "Material3D.h"

#include <math.h>
#include "Mathf.h"

const Material3D Material3D::Default(SolidColor3D::Default, 0.1, 0.9, 0.9, 200);

Material3D::Material3D(const Material3D& material)
	: Material3D(*material.Pattern, material.Ambient, material.Diffuse, material.Specular, material.Shininess)
{ }

Material3D::Material3D(double r, double g, double b, double ambient, double diffuse, double specular, double shininess)
	: Material3D(SolidColor3D(r, g, b), ambient, diffuse, specular, shininess)
{  }

Material3D::Material3D(const ColorPattern& pattern, double ambient, double diffuse, double specular, double shininess)
	: Pattern(&pattern), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess)
{  }

bool Material3D::operator==(const Material3D& other) const
{
	return
		Pattern == other.Pattern &&
		Mathf<double>::Approximately(Ambient, other.Ambient) &&
		Mathf<double>::Approximately(Diffuse, other.Diffuse) &&
		Mathf<double>::Approximately(Specular, other.Specular) &&
		Mathf<double>::Approximately(Shininess, other.Shininess);
}