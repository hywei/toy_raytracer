#ifndef __RENDER_CAMERA_H__
#define __RENDER_CAMERA_H__

#include "_foundation/math/vec3.h"
#include "_foundation/math/ray.h"

namespace raytracer
{
    class Camera
    {
    protected:
        Vec3 origin_{ Vec3(0.f, 0.f, 0.f) };
        Vec3 lower_left_corner_{ Vec3(-2.f, -1.f, -1.f) };
        Vec3 horizontal_{ Vec3(0.f, 2.f, 0.f) };
        Vec3 vertical_{ Vec3(0.f, 2.f, 0.f) };

    public:
        Camera(const Vec3& ori, const Vec3& ll_corner, const Vec3& h, const Vec3& v):
            origin_(ori), lower_left_corner_(ll_corner), horizontal_(h), vertical_(v)
        {}

        Ray getRay(const float u, const float v)
        {
            const Vec3 dir = lower_left_corner_ +
                u * horizontal_ + v * vertical_ - origin_;
            return Ray(origin_, dir.getNormalized());
        }

    };
}

#endif
