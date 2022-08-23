#include "Material3D.h"

#include <math.h>
#include "Mathf.h"

const Material3D Material3D::Default(SolidColor3D::Default, 0.1, 0.9, 0.9, 200, 0);

Material3D::Material3D(const Material3D& material)
	: Material3D(*material.Pattern, material.Ambient, material.Diffuse, material.Specular, material.Shininess, material.Reflective)
{ }

Material3D::Material3D(const ColorPattern& pattern, double ambient, double diffuse, double specular, double shininess, double reflective)
	: Material3D(&pattern, ambient, diffuse, specular, shininess, reflective)
{  }

Material3D::Material3D(const ColorPattern* pattern, double ambient, double diffuse, double specular, double shininess, double reflective)
	: Pattern(pattern), Ambient(ambient), Diffuse(diffuse), Specular(specular), Shininess(shininess), Reflective(reflective)
{  }

bool Material3D::operator==(const Material3D& other) const
{
	return
		Pattern == other.Pattern &&
		Mathf<double>::Approximately(Ambient, other.Ambient) &&
		Mathf<double>::Approximately(Diffuse, other.Diffuse) &&
		Mathf<double>::Approximately(Specular, other.Specular) &&
		Mathf<double>::Approximately(Shininess, other.Shininess) &&
		Mathf<double>::Approximately(Reflective, other.Reflective);
}