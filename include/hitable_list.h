#ifndef WEEKENDRAYTRACER_HITABLE_LIST_H
#define WEEKENDRAYTRACER_HITABLE_LIST_H

#include <vector>
#include "hitable.h"

namespace WeekendRayTracer
{
	class hitable_list: public hitable {
	public:
		hitable_list() {}
		hitable_list(const std::vector<hitable*>& l) { list = std::vector<hitable*>(l); }
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
			hit_record temp_rec;
			bool hit_anything = false;
			double closest_so_far = tmax;
			for (int i = 0; i < list.size(); ++i)
			{
				if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
				{
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return hit_anything;
		}
		std::vector<hitable*> list;
	};
}

#endif //WEEKENDRAYTRACER_HITABLE_LIST_H
