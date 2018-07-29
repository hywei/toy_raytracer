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
        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect)
        {
            const float theta = vfov * RTPi / 180.f;
            const float half_height = RTTan(theta / 2.f);
            const float half_width = aspect * half_height;
            
            origin_ = lookfrom;
            
            const Vec3 w = (lookfrom - lookat).getNormalized();
            const Vec3 u = vup.cross(w).getNormalized();
            const Vec3 v = w.cross(u);

            lower_left_corner_ = origin_ - half_width*u - half_height * v - (lookfrom - lookat);
            lower_left_corner_ = origin_ - half_width*u - half_height * v - w;
            //lower_left_corner_.z = 0.5;

            horizontal_ = 2.f * half_width * u;
            vertical_ = 2 * half_height * v;
        }


        Ray getRay(const float u, const float v)
        {
            const Vec3 dir = lower_left_corner_ +
                u * horizontal_ + v * vertical_ - origin_;
            return Ray(origin_, dir.getNormalized());
        }

    };
}

#endif
