#include <fstream>
#include <random>
#include <iostream>
#include <stdlib.h>

#include "_foundation/math/vec3.h"
#include "_foundation/math/ray.h"
#include "_foundation/math/intersect.h"
#include "_foundation/math/utils.h"
#include "_render/camera.h"
#include "_render/material.h"
#include "_render/scene.h"

using namespace raytracer;


#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#define MAXDEPTH 50

void printProgress(float percentage)
{
    int val = (int)(percentage * 100);
    int lpad = (int)(percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

Vec3 color(const Ray& r, const Scene& scene, int  depth)
{

    HitInfo hit;
    if (scene.raycast(r, hit))
    {
        if (hit.material)
        {
            Ray scattered_ray;
            Vec3 attenuation;

            if (depth < MAXDEPTH &&
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
    std::ofstream fout("res10_4.ppm");
    int nx = 1920, ny = 1080, ns = 1024;
    fout << "P3\n" << nx << " " << ny << "\n255\n";

    Scene scene;

    const Material* mat1 = scene.addLambertianMaterial(Vec3(0.1f, 0.2f, 0.5f));
    const Material* mat2 = scene.addLambertianMaterial(Vec3(0.8f, 0.8f, 0.0f));
    const Material* mat3 = scene.addMetalMaterial(Vec3(0.8f, 0.6f, 0.2f));
    const Material* mat4 = scene.addMetalMaterial(Vec3(0.8f, 0.8f, 0.8f));
    const Material* mat5 = scene.addLambertianMaterial(Vec3(0.f, 0.5f, 0.25f));
    const Material* mat6 = scene.addDielectricMaterial(1.5f);
    const Material* mat7 = scene.addLambertianMaterial(Vec3(0.8f, 0.3f, 0.3f));
    const Material* mat8 = scene.addLambertianMaterial(Vec3(0.f, 0.25f, 0.5f));

    scene.addSphere(Vec3(0.f, 0.f, -1.f), 0.5f, mat1);
    scene.addSphere(Vec3(0.f, -100.5f, -1.f), 100.f, mat2);
    scene.addSphere(Vec3(1.f, 0.f, -1.f), 0.5f, mat3);
    scene.addBox(Vec3(1.5f, 0.f, 0.f), Vec3(0.2f, 0.5f, 0.2f), mat7);
    scene.addBox(Vec3(-1.5f, 0.f, 0.f), Vec3(0.2f, 0.5f, 0.2f), mat8);
    scene.addSphere(Vec3(-1.f, 0.f, -1.f), 0.5f, mat6);
    //scene.addSphere(Vec3(-1.f, 0.f, -1.f), -0.45f, mat6);
    scene.addPlane(Vec3(0.f, 0.f, 1.f), -5.f, mat5);

    const float aspect = static_cast<float>(nx) / static_cast<float>(ny);
    Camera camera(
        Vec3(0.f, 0.f, 1.5f),
        Vec3(0.f, 0.f, -1.f),
        Vec3(0.f, 1.f, 0.f), 
        90, 
        aspect);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.f, 1.f);

    const int total_count = nx * ny;
    int curr_count = 0;
    int percentage = -1;

    std::cout << "Wating for rendering result: \n\n";

    // the ppm viewer draw pixel from left top corner
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
            
            const int curr_percentage = (curr_count * 100) / total_count;

            if (curr_percentage > percentage)
            {
                percentage = curr_percentage;
                printProgress(static_cast<float>(percentage) / 100.f);
            }
            curr_count++;

        }
    fout.close();
    return 0;
}