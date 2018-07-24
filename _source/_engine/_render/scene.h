#ifndef __RENDER_SCENE_H__
#define __RENDER_SCENE_H__

#include <vector>

#include "_foundation/shape.h"
#include "_foundation/math/ray.h"

namespace raytracer
{

    class Scene
    {

    public:
        Scene();
        ~Scene();

        void addSphere(const Vec3& pos, const float radius);
        void addPlane(const Vec3& norm, const float d);
        void addBox(const Vec3& pos, const Vec3& half_extents);

        bool raycast(const Ray& ray, HitInfo& out_hit) const;

    protected:
        std::vector<RTShape*> shapes_;
        std::vector<Geometry*> geometries;
    };
}


#endif
