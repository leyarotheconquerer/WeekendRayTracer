#ifndef WEEKENDRAYTRACER_CAMERA_H
#define WEEKENDRAYTRACER_CAMERA_H

#include <cmath>
#include <math.h>
#include "ray.h"
#include "util.h"

namespace WeekendRayTracer
{
	class camera
	{
	public:
		camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperature, float focus_dist) {
			lens_radius = aperature / 2;
			float theta = vfov * M_PI / 180;
			float half_height = std::tan(theta / 2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);
			lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
			horizontal = 2 * half_width * focus_dist * u;
			vertical = 2 * half_height * focus_dist * v;
		}
		ray get_ray(float s, float t) {
			vec3 rd = lens_radius * random_in_unit_disc();
			vec3 offset = (rd.x() * u) + (rd.y() * v);
			return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}

		vec3 origin;
		vec3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		float lens_radius;
	};
}

#endif //WEEKENDRAYTRACER_CAMERA_H
