#include "Vec3App.h"

void Vec3App::Lerp(Vec3& out, const Vec3& a, const Vec3& b, const float t)
{
	float x = a.x() + t * (b.x() - a.x());
	float y = a.y() + t * (b.y() - a.y());
	float z = a.z() + t * (b.z() - a.z());
	out.set(x, y, z);
}
void Vec3App::LerpArray(Vec3* out, const Vec3* a, const Vec3* b, const float t, const int numVects)
{
	for (int i = 0; i < numVects; i++)
	{
		float x = a[i].x() + t * (b[i].x() - a[i].x());
		float y = a[i].y() + t * (b[i].y() - a[i].y());
		float z = a[i].z() + t * (b[i].z() - a[i].z());
		out[i].set(x, y, z);
	}
}
