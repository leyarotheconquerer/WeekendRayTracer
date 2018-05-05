#ifndef WEEKENDRAYTRACER_UTIL_H
#define WEEKENDRAYTRACER_UTIL_H

namespace WeekendRayTracer
{
	float rand()
	{
		static std::random_device device;
		static std::mt19937 seed(device());
		static std::uniform_real_distribution<float> rand(0.0, 1.0);
		return rand(seed);
	}

	vec3 random_in_unit_sphere() {
		vec3 p;
		do {
			p = 2.0 * vec3(rand(), rand(), rand()) - vec3(1.0, 1.0, 1.0);
		} while(p.squared_length() >= 1.0);
		return p;
	}
}
#endif //WEEKENDRAYTRACER_UTIL_H
