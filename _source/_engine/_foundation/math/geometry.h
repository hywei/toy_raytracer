#ifndef __FOUNDATION_MATH_GEOMETRY_H__
#define __FOUNDATION_MATH_GEOMETRY_H__

#include "_foundation/math/vec3.h"

namespace raytracer
{
    enum class GeometryType
    {
        _sphere,
        _box,
        _plane,
        _count
    };

    class Geometry
    {
    public:
        Geometry(const GeometryType type) : type_(type) {}

        GeometryType getType() const { return type_; }

    protected:
        GeometryType type_;

    };


    class SphereGeometry:
        public Geometry
    {
    public:
        SphereGeometry() : Geometry(GeometryType::_sphere) {}
        SphereGeometry(float r) : Geometry(GeometryType::_sphere), radius(r) {}

    public:
        float radius{ 0.f };
    };

    class BoxGeometry :
        public Geometry
    {
    public:
        BoxGeometry() : Geometry(GeometryType::_sphere) {}
        BoxGeometry(float hx, float hy, float hz) :
            Geometry(GeometryType::_box), half_extents(hx, hy, hz) {}
        BoxGeometry(const Vec3& _half_extents) :
            Geometry(GeometryType::_box), half_extents(_half_extents) {}

    public:
        Vec3 half_extents{ Vec3(0.f, 0.f, 0.f) };
    };

    class PlaneGeometry :
        public Geometry
    {
    public:
        PlaneGeometry() : Geometry(GeometryType::_plane) {}
        PlaneGeometry(const Vec3& n, const float _d) : 
            Geometry(GeometryType::_plane), norm(n), d(_d) {}

    public:
        Vec3 norm{ Vec3(0.f, 0.f, 1.f) };
        float d{ 0.f };
    };
}

#endif
