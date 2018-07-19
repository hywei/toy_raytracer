#ifndef __FOUNDATION_MATH_INTERSECT_H__
#define __FOUNDATION_MATH_INTERSECT_H__

#include "_foundation/math/geometry.h"
#include "_foundation/math/ray.h"

namespace raytracer
{
    namespace intersect
    {
        bool ray_sphere(
            const Ray& ray, 
            const Sphere& sphere, 
            float& out_t, 
            Vec3& out_point)
        {
            const Vec3 m = ray.start - sphere.center;
            const float b = m.dot(ray.dir);
            const float c = m.dot(m) - sphere.radius * sphere.radius;
            if (c > 0.f && b > 0.f) return false;

            const float discr = b * b - c;
            if (discr < 0.f) return false;

            out_t = -b - RTSqrt(discr);

            // if t is negative, ray started inside sphere so clamp t to zero
            if (out_t < 0.f) out_t = 0.f;
            out_point = ray.start + out_t * ray.dir;
            return true;
        }
    }
}

#endif
