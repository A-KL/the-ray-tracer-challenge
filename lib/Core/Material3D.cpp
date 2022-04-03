#include <math.h>
#include "Mathf.h"
#include "Color3D.h"
#include "Material3D.h"

const Material3D Material3D::Default(Color3D::White);

bool Material3D::operator==(const Material3D& other) const
{
	return
		Color == other.Color &&
		Mathf<double>::Approximately(Ambient, other.Ambient) &&
		Mathf<double>::Approximately(Diffuse, other.Diffuse) &&
		Mathf<double>::Approximately(Specular, other.Specular) &&
		Mathf<double>::Approximately(Shininess, other.Shininess);
}