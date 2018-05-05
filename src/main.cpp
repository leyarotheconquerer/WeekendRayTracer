#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"

namespace WeekendRayTracer
{
	float rand()
	{
		static std::random_device device;
		static std::mt19937 seed(device());
		static std::uniform_real_distribution<float> rand(0.0, 1.0);
		return rand(seed);
	}

	vec3 random_in_unit_sphere() {
		vec3 p;
		do {
			p = 2.0 * vec3(rand(), rand(), rand()) - vec3(1.0, 1.0, 1.0);
		} while(p.squared_length() >= 1.0);
		return p;
	}

	vec3 color(const ray& r, hitable *world) {
		hit_record rec;
		if (world->hit(r, 0.0, std::numeric_limits<float>::max(), rec))
		{
			vec3 target = rec.p + rec.normal + random_in_unit_sphere();
			return 0.5 * color(ray(rec.p, target - rec.p), world);
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
	vector<hitable*> list(2);
	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);
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
				col += color(r, world);
			}
			col /= float(ns);
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
	return 0;
}