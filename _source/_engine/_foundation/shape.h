#ifndef __FOUNDATION_SHAPE_H__
#define __FOUNDATION_SHAPE_H__

#include <memory>

#include "_foundation/math/geometry.h"

namespace raytracer
{    
    class RTShape
    {
    public:
        RTShape(Geometry* geometry, const Vec3& pos) : 
            geometry_(geometry), pos_(pos) {}
        
        Geometry* getGeometry() { return geometry_; }
        Geometry* getGeometry() const { return geometry_; }

        Vec3 getPosition() const { return pos_; }
    protected:
        Geometry* geometry_{ nullptr };
        Vec3 pos_{ Vec3(0.f, 0.f, 0.f) };
    };
}

#endif
