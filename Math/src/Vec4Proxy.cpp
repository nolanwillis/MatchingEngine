#include "Vec4Proxy.h"
#include "Trig.h"

Vec4Proxy::Vec4Proxy(float a, float b, float c, float d)
{
	this->x = a * a;
	this->y = b * b;
	this->z = c * c;
	this->w = d * d;
}

Vec4Proxy::operator float() const
{
	return Trig::sqrt(x + y + z + w);
}

float Vec4Proxy::operator*(const Vec4Proxy& r) const
{
	return Trig::sqrt(x + y + z + w) * Trig::sqrt(r.x + r.y + r.z + r.w);
}

bool Vec4Proxy::operator>(const Vec4Proxy& r) const
{
	return (x + y + z + w > r.x + r.y + r.z + r.w);
}
bool Vec4Proxy::operator<(const Vec4Proxy& r) const
{
	return (x + y + z + w < r.x + r.y + r.z + r.w);
}
bool Vec4Proxy::operator==(const Vec4Proxy& r) const
{
	return (x + y + z + w == r.x + r.y + r.z + r.w);
}
bool Vec4Proxy::operator>=(const Vec4Proxy& r) const
{
	return (x + y + z + w >= r.x + r.y + r.z + r.w);
}
bool Vec4Proxy::operator<=(const Vec4Proxy& r) const
{
	return (x + y + z + w <= r.x + r.y + r.z + r.w);
}
bool Vec4Proxy::operator!=(const Vec4Proxy& r) const
{
	return (x + y + z + w != r.x + r.y + r.z + r.w);
}
