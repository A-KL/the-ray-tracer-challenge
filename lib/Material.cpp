#include "Mathf.h"
#include "Color3D.h"
#include "Material.h"

const Material Material::Default(Color3D::White);

bool Material::operator==(const Material& other) const
{
	return
		Color == other.Color &&
		Mathf<double>::Approximately(Ambient, other.Ambient) &&
		Mathf<double>::Approximately(Diffuse, other.Diffuse) &&
		Mathf<double>::Approximately(Specular, other.Specular) &&
		Mathf<double>::Approximately(Shininess, other.Shininess);
}