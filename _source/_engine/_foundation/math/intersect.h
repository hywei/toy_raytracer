#ifndef __FOUNDATION_MATH_INTERSECT_H__
#define __FOUNDATION_MATH_INTERSECT_H__

#include "_foundation/math/geometry.h"
#include "_foundation/shape.h"
#include "_foundation/math/ray.h"

namespace raytracer
{
    namespace intersect
    {
        template<class T>
        bool ray_geometry(
            const Ray& ray,
            const T& geometry,
            const Vec3& pos,
            HitInfo& out_hit);


        template<>
        inline bool ray_geometry<SphereGeometry>(
            const Ray& ray,
            const SphereGeometry& sphere,
            const Vec3& pos,
            HitInfo& out_hit)
        {
            const Vec3 m = ray.start - pos;
            const float b = m.dot(ray.dir);
            const float c = m.dot(m) - sphere.radius * sphere.radius;
            if (c > 0.f && b > 0.f) return false;

            const float discr = b * b - c;
            if (discr < 0.f) return false;

            const float t = -b - RTSqrt(discr);

            // if t is negative, ray started inside sphere so clamp t to zero
            if (t < 0.f) return false;

            out_hit.frac = t;
            out_hit.pos = ray.start + ray.dir * t;
            out_hit.norm = (out_hit.pos - pos).getNormalized();

            return true;
        }

        template<>
        inline bool ray_geometry<PlaneGeometry>(
            const Ray& ray,
            const PlaneGeometry& plane,
            const Vec3& pos,
            HitInfo& out_hit)
        {
            const float f = plane.norm.dot(ray.dir);
            if (RTAbs(f) < FLT_EPSILON) return false;

            const float t = (plane.d - plane.norm.dot(ray.start)) / f;

            if (t <= 0.f) return false;

            out_hit.frac = t;
            out_hit.pos = ray.start + ray.dir * t;
            out_hit.norm = plane.norm;

            return true;
        }

        inline bool ray_shape(const Ray& ray, const RTShape& shape, HitInfo& out_hit)
        {
            const Geometry* geometry = shape.getGeometry();
            if (geometry == nullptr) return false;

            const Vec3& pos = shape.getPosition();
            bool hit = false;

            switch (geometry->getType())
            {
            case GeometryType::_sphere:
                hit = ray_geometry<SphereGeometry>(
                    ray, *static_cast<const SphereGeometry*>(geometry), pos, out_hit);
                break;
            case GeometryType::_plane:
                hit = ray_geometry<PlaneGeometry>(
                    ray, *static_cast<const PlaneGeometry*>(geometry), pos, out_hit);
                break;
            case GeometryType::_box:
                break;
            default:
                break;
            }

            return hit;
        }
    }
}

#endif
