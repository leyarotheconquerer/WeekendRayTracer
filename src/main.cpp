#include <iostream>

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
			float r = float(x) / float(nx);
			float g = float(y) / float(ny);
			float b = 0.2f;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}