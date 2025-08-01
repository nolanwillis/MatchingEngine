#include "Vec2Proxy.h"
#include "Trig.h"

Vec2Proxy::Vec2Proxy(float x, float y)
	:
	x(x * x),
	y(y * y)
{}

Vec2Proxy::operator float() const
{
	return Trig::sqrt(this->x + this->y);
}

float Vec2Proxy::operator*(const Vec2Proxy& rhs) const
{
	return Trig::sqrt(this->x + this->y) * Trig::sqrt(rhs.x + rhs.y);
}

bool Vec2Proxy::operator>(const Vec2Proxy& rhs) const
{
	return (this->x + this->y > rhs.x + rhs.y);
}
bool Vec2Proxy::operator<(const Vec2Proxy& rhs) const
{
	return (this->x + this->y < rhs.x + rhs.y);
}
bool Vec2Proxy::operator==(const Vec2Proxy& rhs) const
{
	return (this->x + this->y == rhs.x + rhs.y);
}
bool Vec2Proxy::operator>=(const Vec2Proxy& rhs) const
{
	return (this->x + this->y >= rhs.x + rhs.y);
}
bool Vec2Proxy::operator<=(const Vec2Proxy& rhs) const
{
	return (this->x + this->y <= rhs.x + rhs.y);
}
bool Vec2Proxy::operator!=(const Vec2Proxy& rhs) const
{
	return (this->x + this->y != rhs.x + rhs.y);
}