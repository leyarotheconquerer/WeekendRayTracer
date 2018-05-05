#ifndef WEEKENDRAYTRACER_HITABLE_H
#define WEEKENDRAYTRACER_HITABLE_H

#include "vec3.h"
#include "ray.h"

namespace WeekendRayTracer
{
	class material;

	struct hit_record
	{
		float t;
		vec3 p;
		vec3 normal;
		material* mat;
	};

	class hitable
	{
	public:
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	};
}

#endif //WEEKENDRAYTRACER_HITABLE_H
