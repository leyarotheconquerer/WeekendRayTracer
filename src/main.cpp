#include <iostream>
#include <limits>
#include <random>
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"

namespace WeekendRayTracer
{
	vec3 color(const ray& r, hitable *world) {
		hit_record rec;
		if (world->hit(r, 0.0, std::numeric_limits<float>::max(), rec))
		{
			return 0.5 * (rec.normal + vec3(1.0f, 1.0f, 1.0f));
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
	random_device device;
	mt19937 seed(device());
	uniform_real_distribution<float> rand(0.0, 1.0);
	for (int y = ny - 1; y >= 0; --y)
	{
		for (int x = 0; x < nx; ++x)
		{
			vec3 col(0.0, 0.0, 0.0);
			for (int s = 0; s < ns; ++s)
			{
				float u = (x + rand(seed)) / float(nx);
				float v = (y + rand(seed)) / float(ny);
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