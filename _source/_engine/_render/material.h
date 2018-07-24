#ifndef __RENDER_MATERIAL_H__
#define __RENDER_MATERIAL_H__

#include "_foundation/math/vec3.h"

namespace raytracer
{
    class Ray;
    class HitInfo;

    class Material
    {
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
        static Vec3 reflect(const Vec3& v, const Vec3& n)
        {
            return v - 2 * v.dot(n) * n;
        }

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
    

}

#endif // !__RENDER_MATERIAL_H__
