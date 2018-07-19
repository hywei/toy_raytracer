#include <fstream>
#include <random>

#include "_foundation/math/vec3.h"
#include "_foundation/math/ray.h"
#include "_foundation/math/intersect.h"
#include "_render/camera.h"

using namespace raytracer;

Vec3 color(const Ray& r)
{
    const Sphere s(Vec3(0.f, 0.f, -1.f), 0.5f);
    float t;
    Vec3 p;
    if (intersect::ray_sphere(r, s, t, p))
    {
        const Vec3 norm = (r.start + r.dir * t - s.center).getNormalized();
        return 0.5f * Vec3(norm.x + 1.f, norm.y + 1.f, norm.z + 1.f);
    }

    t = 0.5f * (r.dir.y + 1.f);
    return (1.f - t) * Vec3(1.f, 1.f, 1.f) + t * Vec3(0.5f, 0.7f, 1.f);
}

int main()
{
    std::ofstream fout("res7.ppm");
    int nx = 200, ny = 100, ns = 100;
    fout << "P3\n" << nx << " " << ny << "\n255\n";

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

                const Ray& r = camera.getRay(u, v);
                col += color(r);
            }


            col /= static_cast<float>(ns);

            const int ir = static_cast <int> (255.99f * col[0]);
            const int ig = static_cast <int> (255.99f * col[1]);
            const int ib = static_cast <int> (255.99f * col[2]);
            fout << ir << " " << ig << " " << ib << std::endl;
        }
    fout.close();
    return 0;
}