#ifndef MATH_TRIG_H
#define MATH_TRIG_H

class Trig
{
public:
	static float cos(const float  angle_radians);
	static float sin(const float  angle_radians);
	static float tan(const float  angle_radians);
	static float atan(const float value);
	static float atan2(const float x, const float y);
	static float acos(const float value);
	static float asin(const float value);
	static void  cossin(float& cos, float& sin, const float angle_radians);
	static float sqrt(const float value);
	static float rsqrt(const float value);
};

#endif
