#include "Vec3Proxy.h"
#include "Trig.h"

Vec3Proxy::Vec3Proxy(float x, float y, float z)
	:
	x(x * x),
	y(y * y),
	z(z * z)
{}

Vec3Proxy::operator float() const
{
	return Trig::sqrt(x + y + z);
}

float Vec3Proxy::operator*(const Vec3Proxy& r) const
{
	return Trig::sqrt(x + y + z) * Trig::sqrt(r.x + r.y + r.z);
}

bool Vec3Proxy::operator>(const Vec3Proxy& r) const
{
	return (x + y + z > r.x + r.y + r.z);
}
bool Vec3Proxy::operator<(const Vec3Proxy& r) const
{
	return (x + y + z < r.x + r.y + r.z);
}
bool Vec3Proxy::operator==(const Vec3Proxy& r) const
{
	return (x + y + z == r.x + r.y + r.z);
}
bool Vec3Proxy::operator>=(const Vec3Proxy& r) const
{
	return (x + y + z >= r.x + r.y + r.z);
}
bool Vec3Proxy::operator<=(const Vec3Proxy& r) const
{
	return (x + y + z <= r.x + r.y + r.z);
}
bool Vec3Proxy::operator!=(const Vec3Proxy& r) const
{
	return (x + y + z != r.x + r.y + r.z);
}
