#ifndef WEEKENDRAYTRACER_DIALECTRIC_H
#define WEEKENDRAYTRACER_DIALECTRIC_H

#include <cmath>
#include "material.h"

namespace WeekendRayTracer
{
	class dialectric : public material
	{
	public:
		dialectric(float ri) : rindex(ri) {}
		bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const {
			vec3 uv = unit_vector(v);
			float dt = dot(uv, n);
			float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
			if (discriminant > 0)
			{
				refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
				return true;
			}
			else
			{
				return false;
			}
		}
		float schlick(float cosine, float rindex) const {
			float r0 = (1 - rindex) / (1 + rindex);
			r0 = r0 * r0;
			return r0 + (1 - r0) * std::pow((1 - cosine), 5);
		}
		virtual bool scatter(const ray& rin, const hit_record& rec, vec3& attenuation, ray& scattered) const {
			vec3 outward_normal;
			vec3 reflected = reflect(rin.direction(), rec.normal);
			float ni_over_nt;
			attenuation = vec3(1.0, 1.0, 1.0);
			vec3 refracted;
			float reflect_prob;
			float cosine;
			if (dot(rin.direction(), rec.normal) > 0)
			{
				outward_normal = -rec.normal;
				ni_over_nt = rindex;
				cosine = rindex * dot(rin.direction(), rec.normal) / rin.direction().length();
			}
			else
			{
				outward_normal = rec.normal;
				ni_over_nt = 1.0 / rindex;
				cosine = -dot(rin.direction(), rec.normal) / rin.direction().length();
			}
			if (refract(rin.direction(), outward_normal, ni_over_nt, refracted))
			{
				reflect_prob = schlick(cosine, rindex);
			}
			else
			{
				reflect_prob = 1.0;
			}
			if (rand() < reflect_prob)
			{
				scattered = ray(rec.p, reflected);
			}
			else
			{
				scattered = ray(rec.p, refracted);
			}
			return true;
		}

		float rindex;
	};
}

#endif //WEEKENDRAYTRACER_DIALECTRIC_H
