#include "Scene3D.h"

#include "RayTracer.h"

Color3D Scene3D::ColorAt(const Ray3D& ray, int remaining) const
{
    auto intersects = ray.Intersect(Shapes);

    auto hits = ray_hit(intersects);

    if (hits.empty())
    {
        return Color3D::Black;
    }

    auto computation = Computation::Prepare(*hits.begin(), ray);

    return ShadeHit(computation, remaining);
}

Color3D Scene3D::ShadeHit(const Computation& computation, int remaining) const
{
    Color3D result(0, 0, 0);

    for (auto& light : Lights)
    {
        auto is_shadow = light
            ->InShadow(computation.OverPosition, Shapes);

        result += light
            ->Compute(computation.Intersect.Shape->Material, *computation.Intersect.Shape, computation.OverPosition, computation.Camera, computation.Normal, is_shadow);
    }

    auto material = computation.Intersect.Shape->Material;
    auto reflected = ReflectedAt(computation, remaining);
    auto refracted = RefractedAt(computation, remaining);

    if (material.Reflective > 0 && material.Transparency > 0)
    {   
        auto reflectance = computation.SchlickValue();

        return result + reflected * reflectance + refracted * (1 - reflectance);
    }

    return result + reflected + refracted;
}

Color3D Scene3D::ReflectedAt(const Computation& comp, int remaining) const
{
    if (remaining <= 0)
    {
        return Color3D::Black;
    }

    if (Mathf<double>::IsZero(comp.Intersect.Shape->Material.Reflective))
    {
        return Color3D::Black;
    }

    auto reflected_ray = Ray3D(comp.OverPosition, comp.Reflection);
    auto color = ColorAt(reflected_ray, remaining - 1);

    return color * comp.Intersect.Shape->Material.Reflective;
}

Color3D Scene3D::RefractedAt(const Computation& comp, const int remaining = 5) const
{
    if (comp.Intersect.Shape->Material.Transparency <= Mathf<double>::Epsilon() || remaining == 0) 
    {
        return Color3D::Black;
    }
    // Find the ratio of first index of refraction to the second.
    // (Yup, this is inverted from the definition of Snell's Law.)
    auto n_ratio = comp.N1 / comp.N2;
    // cos(theta_i) is the same as the dot product of the two vectors
    auto cos_i = Vector3D::Dot(comp.Camera, comp.Normal);
    // Find sin(theta_t)^2 via trigonometric identity
    auto sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);

    if (sin2_t > 1) 
    {
        return Color3D::Black;
    }

    // Find cos(theta_t) via trigonometric identity
    auto cos_t = sqrt(1.0 - sin2_t);
    auto direction = comp.Normal * (n_ratio * cos_i - cos_t) - comp.Camera * n_ratio;
    auto refracted_ray = Ray3D(comp.UnderPosition, direction);

    return ColorAt(refracted_ray, remaining - 1) * comp.Intersect.Shape->Material.Transparency;
}