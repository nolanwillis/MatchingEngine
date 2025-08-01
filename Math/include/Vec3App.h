#ifndef MATH_VEC3_APP_H
#define MATH_VEC3_APP_H

#include "Vec3.h"

class Vec3App
{
public:
	static void Lerp(Vec3& out, const Vec3& a, const Vec3& b, const float t);
	static void LerpArray(Vec3* out, const Vec3* a, const Vec3* b, const float t, const int numVects);
};

#endif 
