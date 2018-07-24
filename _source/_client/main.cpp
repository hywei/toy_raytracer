#include <fstream>
#include <random>

#include "_foundation/math/vec3.h"
#include "_foundation/math/ray.h"
#include "_foundation/math/intersect.h"
#include "_foundation/math/utils.h"
#include "_render/camera.h"
#include "_render/material.h"
#include "_render/scene.h"

using namespace raytracer;


Vec3 color(const Ray& r, const Scene& scene, int  depth)
{

    HitInfo hit;
    if (scene.raycast(r, hit))
    {
        if (hit.material)
        {
            Ray scattered_ray;
            Vec3 attenuation;

            if (depth < 100 &&
                hit.material->scatter(r, hit, attenuation, scattered_ray))
            {
                return attenuation.multiply(color(scattered_ray, scene, depth + 1));
            }
            else
            {
                return Vec3(0.f, 0.f, 0.f);
            }
        }
        else 
        {
            return Vec3(0.f, 0.f, 0.f);
        }
    }
    else
    {
        const float t = 0.5f * (r.dir.y + 1.f);
        return (1.f - t) * Vec3(1.f, 1.f, 1.f) + t * Vec3(0.5f, 0.7f, 1.f);
    }
}

int main()
{
    std::ofstream fout("res8.ppm");
    int nx = 200, ny = 100, ns = 100;
    fout << "P3\n" << nx << " " << ny << "\n255\n";

    Scene scene;

    const Material* mat1 = scene.addLambertianMaterial(Vec3(0.8f, 0.3f, 0.3f));
    const Material* mat2 = scene.addLambertianMaterial(Vec3(0.8f, 0.8f, 0.0f));
    const Material* mat3 = scene.addMetalMaterial(Vec3(0.8f, 0.6f, 0.2f));
    const Material* mat4 = scene.addMetalMaterial(Vec3(0.8f, 0.8f, 0.8f));
    const Material* mat5 = scene.addLambertianMaterial(Vec3(0.f, 0.18f, 0.4f));

    scene.addSphere(Vec3(0.f, 0.f, -1.f), 0.5f, mat1);
    scene.addSphere(Vec3(0.f, -100.5f, -1.f), 100.f, mat2);
    scene.addSphere(Vec3(1.f, 0.f, -1.f), 0.3f, mat3);
    scene.addSphere(Vec3(-1.f, 0.f, -1.f), 0.3f, mat4);
    scene.addPlane(Vec3(0.f, 0.f, 1.f), -2.f, mat5);

    const Vec3 lower_left_corner(-2.f, -1.f, -1.f);
    const Vec3 horizontal(4.f, 0.f, 0.f);
    const Vec3 vertical(0.f, 2.f, 0.f);
    const Vec3 origin(0.f, 0.f, 0.f);

    Camera camera(origin, lower_left_corner, horizontal, vertical);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.f, 1.f);

    for (int j = ny - 1; j >= 0; --j)
        for (int i = 0; i < nx; ++i)
        {
            Vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; ++s)
            {
                const float u = 
                    (static_cast<float>(i) + dis(gen)) / static_cast<float> (nx);
                const float v =
                    (static_cast<float>(j) + dis(gen)) / static_cast<float> (ny);

                const Ray& ray = camera.getRay(u, v);
                col += color(ray, scene, 0);
            }


            col /= static_cast<float>(ns);
            col = Vec3(RTSqrt(col[0]), RTSqrt(col[1]), RTSqrt(col[2]));

            const int ir = static_cast <int> (255.99f * col[0]);
            const int ig = static_cast <int> (255.99f * col[1]);
            const int ib = static_cast <int> (255.99f * col[2]);
            fout << ir << " " << ig << " " << ib << std::endl;
        }
    fout.close();
    return 0;
}