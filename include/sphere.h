#ifndef WEEKENDRAYTRACER_SPHERE_H
#define WEEKENDRAYTRACER_SPHERE_H

#include <cmath>
#include "hitable.h"

namespace WeekendRayTracer
{
	class sphere : public hitable
	{
	public:
		sphere() {}
		sphere(vec3 cen, float r, material* mat) : center(cen), radius(r), mat(mat) {}
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
			vec3 oc = r.origin() - center;
			float a = dot(r.direction(), r.direction());
			float b = dot(oc, r.direction()); // If you don't multiply by 2 here, the rest of the constants cancel out
			float c = dot(oc, oc) - radius * radius;
			float discriminant = b*b - a*c;
			if (discriminant > 0)
			{
				float temp = (-b - std::sqrt(discriminant)) / a;
				if (temp < tmax && temp > tmin)
				{
					rec.t = temp;
					rec.p = r.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat = mat;
					return true;
				}
				temp = (-b + std::sqrt(discriminant)) / a;
				if (temp < tmax	 && temp > tmin)
				{
					rec.t = temp;
					rec.p = r.point_at_parameter(rec.t);
					rec.normal = (rec.p - center) / radius;
					rec.mat = mat;
					return true;
				}
			}
			return false;
		}

		vec3 center;
		float radius;
		material* mat;
	};
}

#endif //WEEKENDRAYTRACER_SPHERE_H
