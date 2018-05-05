#ifndef WEEKENDRAYTRACER_METAL_H
#define WEEKENDRAYTRACER_METAL_H

#include "material.h"

namespace WeekendRayTracer
{
	class metal : public material
	{
	public:
		metal(const vec3& a) : albedo(a) {}
		virtual bool scatter(const ray& rin, const hit_record& rec, vec3& attenuation, ray& scattered) const {
			vec3 reflected = reflect(unit_vector(rin.direction()), rec.normal);
			scattered = ray(rec.p, reflected);
			attenuation = albedo;
			return dot(scattered.direction(), rec.normal) > 0;
		}

		vec3 albedo;
	};
}

#endif //WEEKENDRAYTRACER_METAL_H
