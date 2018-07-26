#ifndef __RENDER_MATERIAL_H__
#define __RENDER_MATERIAL_H__

#include "_foundation/math/vec3.h"

namespace raytracer
{
    class Ray;
    class HitInfo;

    class Material
    {
    protected:
        static Vec3 reflect(const Vec3& v, const Vec3& n);
        static bool refract(const Vec3& v, const Vec3& n,
            float ni_over_nt, Vec3& out_refracted);
        static float schlick(float cosine, float ref_idx);

    public:
        virtual ~Material() {}
        virtual bool scatter(
            const Ray& ray_in,
            const HitInfo& hit,
            Vec3& out_attenuation,
            Ray& out_scattered_ray) const = 0;
    };

    class LambertianMaterial :
        public Material
    {
    public:
        LambertianMaterial(const Vec3& albedo) : albedo_(albedo) {}
        virtual ~LambertianMaterial() {}

        bool scatter(
            const Ray& ray_in,
            const HitInfo& hit,
            Vec3& out_attenuation,
            Ray& out_scattered_ray) const override;

    protected:
        Vec3 albedo_;
    };

    class MetalMaterial :
        public Material
    {
    protected:

    public:
        MetalMaterial(const Vec3& albedo) : albedo_(albedo) {}
        virtual ~MetalMaterial() {}

        bool scatter(
            const Ray& ray_in,
            const HitInfo& hit,
            Vec3& out_attenuation,
            Ray& out_scattered_ray) const override;

    protected:
        Vec3 albedo_;
    };
    
    class DielectricMaterial :
        public Material
    {
    public:
        DielectricMaterial(float ri) : ref_idx_(ri) {}
        bool scatter(
            const Ray& ray_in,
            const HitInfo& hit,
            Vec3& out_attenuation,
            Ray& out_scattered_ray) const override;

    protected:
        float ref_idx_;

    };
}

#endif // !__RENDER_MATERIAL_H__
