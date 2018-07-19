#ifndef __FOUNDATION_MATH_GEOMETRY_H__
#define __FOUNDATION_MATH_GEOMETRY_H__

#include "_foundation/math/vec3.h"

namespace raytracer
{
    class Sphere
    {
    public:
        Sphere(const Vec3& c, const float r) : center(c), radius(r) {}

    public:
        float radius{ 0.f };
        Vec3 center;
    };
}

#endif
