#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
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
}

using namespace WeekendRayTracer;
using namespace std;

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	vector<material*> materials = {
		new lambertian(vec3(0.8, 0.3, 0.3)),
		new lambertian(vec3(0.8, 0.8, 0.0)),
		new metal(vec3(0.8, 0.6, 0.2)),
		new metal(vec3(0.8, 0.8, 0.8))
	};
	vector<hitable*> list = {
		new sphere(vec3(0.0, 0.0, -1.0), 0.5, materials[0]),
		new sphere(vec3(0.0, -100.5, -1.0), 100, materials[1]),
		new sphere(vec3(1.0, 0.0, -1.0), 0.5, materials[2]),
		new sphere(vec3(-1.0, 0.0, -1.0), 0.5, materials[3]),
	};
	hitable* world = new hitable_list(list);
	camera cam;
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