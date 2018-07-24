#include "_render/material.h"

#include "_foundation/math/ray.h"
#include "_foundation/math/utils.h"

namespace raytracer
{
    bool LambertianMaterial::scatter(
        const Ray& ray_in,
        const HitInfo& hit,
        Vec3& out_attenuation,
        Ray& out_scattered_ray) const
    {
        Vec3 target = hit.pos + hit.norm + randomPointInSphere(1.f);
        out_scattered_ray = Ray(hit.pos, (target - hit.pos).getNormalized());
        out_attenuation = albedo_;

        return true;
    }

    bool MetalMaterial::scatter(
        const Ray& ray_in,
        const HitInfo& hit,
        Vec3& out_attenuation,
        Ray& out_scattered_ray) const
    {
        Vec3 reflected = reflect(ray_in.dir, hit.norm);
        out_scattered_ray = Ray(hit.pos, reflected);
        out_attenuation = albedo_;

        return (out_scattered_ray.dir.dot(hit.norm) > 0.f);
    }
}