#ifndef WEEKENDRAYTRACER_MATERIAL_H
#define WEEKENDRAYTRACER_MATERIAL_H

#include "ray.h"
#include "hitable.h"

namespace WeekendRayTracer
{
	class material
	{
	public:
		virtual bool scatter(const ray& rin, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
	};
}

#endif //WEEKENDRAYTRACER_MATERIAL_H
