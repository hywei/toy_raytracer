#ifndef __RENDER_SCENE_H__
#define __RENDER_SCENE_H__

#include <vector>

#include "_foundation/math/ray.h"

namespace raytracer
{
    class Material;
    class RTShape;
    class Geometry;

    class Scene
    {

    public:
        Scene();
        ~Scene();

        void addSphere(const Vec3& pos, float radius, const Material* material);
        void addPlane(const Vec3& norm, float d, const Material* material);
        void addBox(const Vec3& pos, const Vec3& half_extents, const Material* material);

        bool raycast(const Ray& ray, HitInfo& out_hit) const;

        const Material* addLambertianMaterial(const Vec3& albedo);
        const Material* addMetalMaterial(const Vec3& albedo);

    protected:
        std::vector<RTShape*> shapes_;
        std::vector<Geometry*> geometries_;

        std::vector<Material*> materials_;
    };
}


#endif
