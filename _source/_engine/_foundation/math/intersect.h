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

        template<>
        inline bool ray_geometry<BoxGeometry>(
            const Ray& ray,
            const BoxGeometry& box,
            const Vec3& pos,
            HitInfo& out_hit)
        {
            const Vec3 box_min = pos - box.half_extents;
            const Vec3 box_max = pos + box.half_extents;

            float tmin = std::numeric_limits<float>::min();
            float tmax = std::numeric_limits<float>::max();

            for (unsigned int i = 0; i < 3; ++i) {
                if (RTAbs(ray.dir[i]) < FLT_EPSILON) {
                    if (ray.start[i] < box_min[i] || ray.start[i] > box_max[i])
                        return false;
                }
                else {
                    const float odd = 1.f / ray.dir[i];
                    float t1 = (box_min[i] - ray.start[i]) * odd;
                    float t2 = (box_max[i] - ray.start[i]) * odd;
                    if (t1 > t2) std::swap(t1, t2);
                    if (t1 > tmin) tmin = t1;
                    if (t2 < tmax) tmax = t2;
                    if (tmin > tmax || tmax < 0) return false;
                }
            }

            out_hit.frac = tmin;
            out_hit.pos = ray.start + ray.dir * tmin;

            const Vec3 q = out_hit.pos - pos;
            const int nx = static_cast<int>(q.x / RTAbs(box.half_extents.x));
            const int ny = static_cast<int>(q.y / RTAbs(box.half_extents.y));
            const int nz = static_cast<int>(q.z / RTAbs(box.half_extents.z));

            out_hit.norm = Vec3(
                static_cast<float>(nx), 
                static_cast<float>(ny), 
                static_cast<float>(nz)).getNormalized();

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
                hit = ray_geometry<BoxGeometry>(
                    ray, *static_cast<const BoxGeometry*>(geometry), pos, out_hit);
                break;
            default:
                break;
            }

            if (hit && RTAbs(out_hit.frac) < 1e-6f) return false;

            out_hit.material = shape.getMaterial();

            return hit;
        }

    }
}

#endif
