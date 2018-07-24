#ifndef __FOUNDATION_MATH_RAY_H__
#define __FOUNDATION_MATH_RAY_H__

#include "_foundation/math/vec3.h"

namespace raytracer
{
    class Ray
    {
    public:
        Ray() {}

        Ray(const Vec3& s, const Vec3& d) : start(s), dir(d) {}

        Vec3 origin() const { return start; }
        Vec3 direction() const { return dir; }

    public:
        Vec3 start{ Vec3(0.f, 0.f, 0.f) };
        Vec3 dir{ Vec3(0.f, 0.f, 1.f) };
    };

    class HitInfo
    {
    public:
        float frac{ -1.f };
        Vec3 pos{ Vec3(0.f, 0.f, 0.f) };
        Vec3 norm{ Vec3(0.f, 0.f, 1.f) };
    };
}

#endif