#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "dialectric.h"
#include "util.h"

namespace WeekendRayTracer
{
	vec3 color(const ray& r, hitable *world, int depth) {
		hit_record rec;
		if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
		{
			ray scattered;
			vec3 attenuation;
			if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered))
			{
				return attenuation * color(scattered, world, depth + 1);
			}
			else
			{
				return vec3(0.0, 0.0, 0.0);
			}
		}
		else
		{
			vec3 unit_direction = unit_vector(r.direction());
			float t = 0.5f * (unit_direction.y() + 1.0f);
			return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
		}
	}

	hitable* random_scene(std::vector<hitable*>& hitables, std::vector<material*>& materials) {
		int n = 500;
		materials.push_back(new lambertian(vec3(0.5, 0.5, 0.5)));
		hitables.push_back(new sphere(vec3(0.0, -1000.0, 0.0), 1000, materials.back()));
		int val = 5;
		for (int a = -val; a < val; ++a)
		{
			for (int b = -val; b < val; ++b)
			{
				float choose_mat = rand();
				vec3 center(a + 0.9 * rand(), 0.2, b + 0.9*rand());
				if ((center - vec3(4.0, 0.2, 0)).length() > 0.9)
				{
					if (choose_mat < 0.95)
					{
						materials.push_back(new lambertian(vec3(rand() * rand(), rand() * rand(), rand() * rand())));
					}
					else if (choose_mat < 0.95)
					{
						materials.push_back(new metal(vec3(0.5 * (1 + rand()), 0.5*(1 + rand()), 0.5 * (1 + rand())), 0.5 * rand()));
					}
					else
					{
						materials.push_back(new dialectric(1.5));
					}
					hitables.push_back(new sphere(center, 0.2, materials.back()));
				}
			}
		}
		materials.push_back(new dialectric(1.5));
		hitables.push_back(new sphere(vec3(0, 1, 0), 1.0, materials.back()));
		materials.push_back(new lambertian(vec3(0.4, 0.2, 0.1)));
		hitables.push_back(new sphere(vec3(-4, 1, 0), 1.0, materials.back()));
		materials.push_back(new metal(vec3(0.7, 0.6, 0.5), 0.0));
		hitables.push_back(new sphere(vec3(4, 1, 0), 1.0, materials.back()));
		return new hitable_list(hitables);
	}
}

using namespace WeekendRayTracer;
using namespace std;

int main()
{
	int nx = 800;
	int ny = 600;
	int ns = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	vector<material*> materials = {
	};
	vector<hitable*> list = {
	};
	hitable* world = random_scene(list, materials);
	vec3 lookfrom(11.0, 2.0, 2.5);
	vec3 lookat(0.0, 0.25, -1.0);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperature = 0.0;
	camera cam(lookfrom, lookat, vec3(0.0, 1.0, 0.0), 20, float(nx) / float(ny), aperature, dist_to_focus);
	for (int y = ny - 1; y >= 0; --y)
	{
		for (int x = 0; x < nx; ++x)
		{
			vec3 col(0.0, 0.0, 0.0);
			for (int s = 0; s < ns; ++s)
			{
				float u = (x + WeekendRayTracer::rand()) / float(nx);
				float v = (y + WeekendRayTracer::rand()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
			int ir = int(col.r() * 255.99);
			int ib = int(col.b() * 255.99);
			int ig = int(col.g() * 255.99);
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	for(hitable* obj : list)
	{
		delete obj;
	}
	for(material* mat : materials)
	{
		delete mat;
	}
	return 0;
}