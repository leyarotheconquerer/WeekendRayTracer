#include <iostream>
#include "vec3.h"
#include "ray.h"

namespace WeekendRayTracer
{
	float hit_sphere(const vec3& center, float radius, const ray& r) {
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = 2.0f * dot(oc, r.direction());
		float c = dot(oc, oc) - radius * radius;
		float discriminant = b*b - 4*a*c;
		if (discriminant >= 0.0f)
		{
			return (-b - std::sqrt(discriminant)) / (2.0f * a);
		}
		else
		{
			return -1.0f;
		}
	}

	vec3 color(const ray& r) {
		float t = hit_sphere(vec3(0.0, 0.0, -1.0f), 0.5, r);
		if (t > 0.0f) {
			vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
			return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
		}
		vec3 unit_direction = unit_vector(r.direction());
		t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

using namespace WeekendRayTracer;
using namespace std;

int main()
{
	int nx = 200;
	int ny = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	for (int y = ny - 1; y >= 0; --y)
	{
		for (int x = 0; x < nx; ++x)
		{
			float u = float(x) / float(nx);
			float v = float(y) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(col.r() * 255.99);
			int ib = int(col.b() * 255.99);
			int ig = int(col.g() * 255.99);
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}