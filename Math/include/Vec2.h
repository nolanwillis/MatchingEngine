#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include "Constants.h"
#include "Enum.h"
#include "Vec2Proxy.h"

// SIMD includes.
#include <xmmintrin.h>
#include <smmintrin.h> 

class Vec3;
class Vec4;

class Vec2
{
public:
	friend class Vec3;
	friend class Vec4;

	Vec2();
	Vec2(const float x, const float y);
	Vec2(const Vec2& rhs);
	explicit Vec2(const Vec3& rhs);
	explicit Vec2(const Vec4& rhs);
	Vec2& operator=(const Vec2& rhs);
	Vec2& operator=(const Vec3& rhs);
	Vec2& operator=(const Vec4& rhs);
	Vec2(Vec2&& rhs) = default;
	Vec2& operator = (Vec2&& rhs) = default;
	~Vec2() = default;

	float& operator[] (const enum x_enum);
	float& operator[] (const enum y_enum);
	float operator[] (const enum x_enum) const;
	float operator[] (const enum y_enum) const;	
	float x() const;
	float y() const;
	void x(const float x);
	void y(const float y);
	void set(const float x, const float y);
	void set(const Vec2& inVec2);
	void set(const Vec3& inVec3);
	void set(const Vec4& inVec4);

	Vec2 operator + () const;
	Vec2 operator + (const Vec2& inVec2) const;
	Vec2& operator += (const Vec2& inVec2);

	Vec2 operator - () const;
	Vec2 operator - (const Vec2& inVec2) const;
	Vec2& operator -= (const Vec2& inVec2);

	Vec2 operator * (const float scale) const;
	friend Vec2 operator * (const float scale, const Vec2& inVec2);
	Vec2& operator *= (const float scale);

	Vec2& norm();
	Vec2 getNorm() const;
	Vec2Proxy len() const;

	bool isEqual(const Vec2& v, const float epsilon = MATH_TOLERANCE) const;
	bool isZero(const float epsilon = MATH_TOLERANCE) const;

	void Print(const char* pName) const;

private:
	union
	{
		__m128	_mv;

		struct
		{
			float _vx;
			float _vy;
		};
	};
};

#endif

