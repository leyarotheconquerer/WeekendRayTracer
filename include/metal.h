#ifndef WEEKENDRAYTRACER_METAL_H
#define WEEKENDRAYTRACER_METAL_H

#include "material.h"
#include "util.h"

namespace WeekendRayTracer
{
	class metal : public material
	{
	public:
		metal(const vec3& a, float f) : albedo(a) {
			fuzz = (f < 1.0 ? f : 1.0);
		}
		virtual bool scatter(const ray& rin, const hit_record& rec, vec3& attenuation, ray& scattered) const {
			vec3 reflected = reflect(unit_vector(rin.direction()), rec.normal);
			scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
			attenuation = albedo;
			return dot(scattered.direction(), rec.normal) > 0;
		}

		vec3 albedo;
		float fuzz;
	};
}

#endif //WEEKENDRAYTRACER_METAL_H
