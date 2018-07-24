#ifndef __FOUNDATION_MATH_UTILS_H__
#define __FOUNDATION_MATH_UTILS_H__

#include <random>

#include "_foundation/math/vec3.h"

namespace raytracer
{
    Vec3 randomPointInSphere(const float radius)
    {
        Vec3 p;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-radius, radius);

        do {
            p = Vec3(dis(gen), dis(gen), dis(gen));
        } while (p.dot(p) >= radius * radius);

        return p;
    }
}

#endif
