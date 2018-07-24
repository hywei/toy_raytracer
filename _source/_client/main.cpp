#include <fstream>
#include <random>

#include "_foundation/math/vec3.h"
#include "_foundation/math/ray.h"
#include "_foundation/math/intersect.h"
#include "_foundation/math/utils.h"
#include "_render/camera.h"
#include "_render/scene.h"

using namespace raytracer;


Vec3 color(const Ray& r, const Scene& scene)
{

    HitInfo hit;
    if (scene.raycast(r, hit))
    {
        Vec3 target = hit.pos + hit.norm + randomPointInSphere(1.f);
        const Ray new_ray(hit.pos, (target - hit.pos).getNormalized());
        //return 0.5 * Vec3(hit.norm.x + 1.f, hit.norm.y + 1.f, hit.norm.z + 1.f);
        return 0.5f * color(new_ray, scene);
    }
    else
    {
        const float t = 0.5f * (r.dir.y + 1.f);
        return (1.f - t) * Vec3(1.f, 1.f, 1.f) + t * Vec3(0.5f, 0.7f, 1.f);
    }
}

int main()
{
    std::ofstream fout("res7_1.ppm");
    int nx = 200, ny = 100, ns = 100;
    fout << "P3\n" << nx << " " << ny << "\n255\n";

    Scene scene;
    scene.addSphere(Vec3(0.f, 0.f, -1.f), 0.5f);
    scene.addSphere(Vec3(0.f, -100.5f, -1.f), 100.f);
    //scene.addPlane(Vec3(0.f, 1.f, 0.f), -2.f);

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
                col += color(ray, scene);
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