#ifndef WEEKENDRAYTRACER_VEC3_H
#define WEEKENDRAYTRACER_VEC3_H

#include <cmath>
#include <istream>
#include <ostream>

namespace WeekendRayTracer
{
	class vec3 {
	public:
		vec3() {}
		vec3(float e0, float e1, float e2) {
			e[0] = e0; e[1] = e1; e[2] = e2;
		}
		inline float x() const { return e[0]; }
		inline float y() const { return e[1]; }
		inline float z() const { return e[2]; }
		inline float r() const { return e[0]; }
		inline float g() const { return e[1]; }
		inline float b() const { return e[2]; }

		inline const vec3& operator+() const { return *this; }
		inline vec3 operator-() const { return vec3(-x(), -y(), -z()); }
		inline float operator[](int i) const { return e[i]; }
		inline float& operator[](int i) { return e[i]; }

		inline vec3& operator+=(const vec3 &v2) {
			e[0] += v2.x(); e[1] += v2.x(); e[2] += v2.x();
			return *this;
		}
		inline vec3& operator-=(const vec3 &v2) {
			e[0] -= v2.x(); e[1] -= v2.x(); e[2] -= v2.x();
			return *this;
		}
		inline vec3& operator*=(const vec3 &v2) {
			e[0] *= v2.x(); e[1] *= v2.x(); e[2] *= v2.x();
			return *this;
		}
		inline vec3& operator/=(const vec3 &v2) {
			e[0] /= v2.x(); e[1] /= v2.x(); e[2] /= v2.x();
			return *this;
		}
		inline vec3& operator*=(const float t) {
			e[0] *= t; e[1] *= t; e[2] *= t;
			return *this;
		}
		inline vec3& operator/=(const float t) {
			e[0] /= t; e[1] /= t; e[2] /= t;
			return *this;
		}

		inline float length() const {
			return std::sqrt(squared_length());
		}
		inline float squared_length() const {
			return x() * x() + y() * y() + z() * z();
		}
		inline void make_unit_vector() {
			float k = 1.0 / length();
			e[0] *= k; e[1] *= k; e[2] *= k;
		}

		float e[3];
	};

	inline std::istream& operator>>(std::istream& is, vec3& t) {
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	inline std::ostream& operator<<(std::ostream& os, const vec3& t) {
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	inline vec3 operator+(const vec3& v1, const vec3& v2) {
		return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
	}

	inline vec3 operator-(const vec3& v1, const vec3& v2) {
		return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
	}

	inline vec3 operator*(const vec3& v1, const vec3& v2) {
		return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
	}

	inline vec3 operator/(const vec3& v1, const vec3& v2) {
		return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
	}

	inline vec3 operator*(float f, const vec3& v) {
		return vec3(v.x() * f, v.y() * f, v.z() * f);
	}

	inline vec3 operator/(const vec3& v, float f) {
		return vec3(v.x() / f, v.y() / f, v.z() / f);
	}

	inline vec3 operator*(const vec3& v, float f) {
		return vec3(v.x() * f, v.y() * f, v.z() * f);
	}

	inline float dot(const vec3& v1, const vec3& v2) {
		return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
	}

	inline vec3 cross(const vec3& v1, const vec3& v2) {
		return vec3	(
			v1.y() * v2.z() - v1.z() * v2.y(),
			-v1.x() * v2.z() - v1.z() * v2.x(),
			v1.x() * v2.y() - v1.y() * v2.x()
		);
	}

	inline vec3 unit_vector(const vec3& v) {
		return v / v.length();
	}
}

#endif //WEEKENDRAYTRACER_VEC3_H
