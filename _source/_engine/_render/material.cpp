#include "_render/material.h"

#include "_foundation/math/ray.h"
#include "_foundation/math/utils.h"

namespace raytracer
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.f, 1.f);

    Vec3 Material::reflect(const Vec3& v, const Vec3& n)
    {
        return v - 2 * v.dot(n) * n;
    }

    bool Material::refract(
        const Vec3& v,
        const Vec3& n,
        float ni_over_nt,
        Vec3& out_refracted)
    {
        const float dt = v.getNormalized().dot(n);
        const float discriminant = 1.f - ni_over_nt * ni_over_nt * (1 - dt*dt);
        if (discriminant > 0){
            out_refracted = ni_over_nt * (v - n * dt) - n * RTSqrt(discriminant);
            return true;
        }
        return false;
    }

    float Material::schlick(float cosine, float ref_idx)
    {
        const float r0 = (1 - ref_idx) / (1 + ref_idx);
        const float square_r0 = r0 * r0;
        return square_r0 + (1 - square_r0) * std::pow((1 - cosine), 5);
    }

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

    bool DielectricMaterial::scatter(
        const Ray& ray_in,
        const HitInfo& hit,
        Vec3& out_attenuation,
        Ray& out_scattered_ray) const
    {
        const Vec3 reflected_dir = reflect(ray_in.dir, hit.norm);
        out_attenuation = Vec3(1.f, 1.f, 1.f);

        Vec3 outward_norm;
        float ni_over_nt = 0.f;
        float cosine = 0.f;
        if (ray_in.dir.dot(hit.norm) > 0) {
            outward_norm = -hit.norm;
            ni_over_nt = ref_idx_;
            cosine = ref_idx_ * ray_in.dir.dot(hit.norm);
        }
        else {
            outward_norm = hit.norm;
            ni_over_nt = 1.f / ref_idx_;
            cosine = -ray_in.dir.dot(hit.norm);
        }

        float reflect_prob = 0.f;
        Vec3 refracted_dir;
        if (refract(ray_in.dir, outward_norm, ni_over_nt, refracted_dir)) {
            reflect_prob = schlick(cosine, ref_idx_);
        }
        else {
            out_scattered_ray = Ray(hit.pos, reflected_dir.getNormalized());
            reflect_prob = 1.f;
        }

        if (dis(gen) < reflect_prob){
            out_scattered_ray = Ray(hit.pos, reflected_dir.getNormalized());
        }
        else {
            out_scattered_ray = Ray(hit.pos, refracted_dir.getNormalized());
        }


        return true;
    }
}