#include <math.h>
#include "Trig.h"

float Trig::cos(const float angle_radians)
{
	return cosf(angle_radians);
}
float Trig::sin(const float angle_radians)
{
	return sinf(angle_radians);
}
float Trig::tan(const float angle_radians)
{
	return tanf(angle_radians);
}
float Trig::atan(const float value)
{
	return atanf(value);
}
float Trig::atan2(const float x, const float y)
{
	return atan2f(x, y);
}
float Trig::acos(const float value)
{
	return acosf(value);
}
float Trig::asin(const float value)
{
	return asinf(value);
}
void Trig::cossin(float& cos, float& sin, const float angle_radians)
{
	cos = cosf(angle_radians);
	sin = sinf(angle_radians);
}
float Trig::sqrt(const float value)
{
	return sqrtf(value);
}
float Trig::rsqrt(const float value)
{
	return 1 / sqrtf(value);
}
