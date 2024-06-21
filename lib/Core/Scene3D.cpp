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

        result += ReflectedAt(computation, remaining);
    }

    return result;
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

    Ray3D reflected_ray(comp.OverPosition, comp.Reflection);
    auto color = this->ColorAt(reflected_ray, remaining - 1);

    return color * comp.Intersect.Shape->Material.Reflective;
}