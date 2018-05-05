#ifndef WEEKENDRAYTRACER_CAMERA_H
#define WEEKENDRAYTRACER_CAMERA_H

#include <cmath>
#include <math.h>
#include "ray.h"

namespace WeekendRayTracer
{
	class camera
	{
	public:
		camera(float vfov, float aspect) {
			float theta = vfov * M_PI / 180;
			float half_height = std::tan(theta / 2);
			float half_width = aspect * half_height;
			lower_left_corner = vec3(-half_width, -half_height, -1.0);
			horizontal = vec3(2 * half_width, 0.0, 0.0);
			vertical = vec3(0.0, 2 * half_height, 0.0);
			origin = vec3(0.0, 0.0, 0.0);
		}
		ray get_ray(float u, float v) {
			return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}

		vec3 origin;
		vec3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
	};
}

#endif //WEEKENDRAYTRACER_CAMERA_H
