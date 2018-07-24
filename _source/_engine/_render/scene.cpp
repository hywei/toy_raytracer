#include <cassert>

#include "_render/scene.h"
#include "_render/material.h"
#include "_foundation/math/intersect.h"

namespace raytracer
{
    Scene::Scene() {}

    Scene::~Scene() 
    {
        for (auto geo : geometries_) delete(geo);
        for (auto shape : shapes_) delete(shape);
        for (auto material : materials_) delete(material);
    }

    void Scene::addSphere(const Vec3& pos, float radius, const Material* material)
    {
        SphereGeometry* sphere_geometry = new SphereGeometry(radius);
        RTShape* shape = new RTShape(sphere_geometry, pos);
        shape->setMaterial(material);

        geometries_.emplace_back(sphere_geometry);
        shapes_.emplace_back(shape);
    }

    void Scene::addPlane(const Vec3& norm, float d, const Material* material)
    {
        PlaneGeometry* plane_geometry = new PlaneGeometry(norm, d);
        RTShape* shape = new RTShape(plane_geometry, Vec3(0.f, 0.f, 0.f));
        shape->setMaterial(material);

        geometries_.emplace_back(plane_geometry);
        shapes_.emplace_back(shape);
    }

    void Scene::addBox(const Vec3& pos, const Vec3& half_extents, const Material* material)
    {
        BoxGeometry* box_geometry = new BoxGeometry(half_extents);
        RTShape* shape = new RTShape(box_geometry, pos);
        shape->setMaterial(material);

        geometries_.emplace_back(box_geometry);
        shapes_.emplace_back(shape);
    }

    const Material* Scene::addLambertianMaterial(const Vec3& albedo)
    {
        LambertianMaterial* material = new LambertianMaterial(albedo);
        materials_.emplace_back(static_cast<Material*>(material));
        return material;
    }

    const Material* Scene::addMetalMaterial(const Vec3& albedo)
    {
        MetalMaterial* material = new MetalMaterial(albedo);
        materials_.emplace_back(static_cast<Material*>(material));
        return material;
    }

    bool Scene::raycast(const Ray& ray, HitInfo& out_hit) const
    {
        out_hit.frac = std::numeric_limits<float>::max();

        bool has_hit = false;
        for (auto shape : shapes_)
        {
            HitInfo hit;
            if (intersect::ray_shape(ray, *shape, hit))
            {
                assert(hit.frac > 0.f);
                if (hit.frac < out_hit.frac)
                {
                    out_hit = hit;
                }
                has_hit = true;
            }
        }

        return has_hit;
    }
}
