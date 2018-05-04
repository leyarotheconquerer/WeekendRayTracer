#include <iostream>
#include "vec3.h"

using namespace WeekendRayTracer;
using namespace std;

int main()
{
	int nx = 200;
	int ny = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = 0; y < ny; ++y)
	{
		for (int x = 0; x < nx; ++x)
		{
			vec3 col(float(x) / float(nx), float(y) / float(ny), 0.2f);
			int ir = col.r() * 255.99;
			int ib = col.b() * 255.99;
			int ig = col.g() * 255.99;
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}