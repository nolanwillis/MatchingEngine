#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "Constants.h"
#include "Enum.h"
#include "Vec4Proxy.h"

// SIMD includes.
#include <xmmintrin.h>
#include <smmintrin.h> 

class Mat4;
class Vec2;
class Vec3;

class Vec4
{
public:
	friend class Mat3;
	friend class Trans;
	friend class Vec2;
	friend class Vec3;

	Vec4();
	Vec4(const float in_x, const float in_y, const float in_z, const float in_w);
	Vec4(const Vec3& inVec3, const float w);
	explicit Vec4(const Vec2& rhs);
	explicit Vec4(const Vec3& rhs);
	Vec4(const Vec4& rhs);
	Vec4& operator=(const Vec2& rhs);
	Vec4& operator=(const Vec3& rhs);
	Vec4& operator=(const Vec4& rhs);
	Vec4(Vec4&& rhs) = default;
	Vec4& operator=(Vec4&& rhs) = default;
	~Vec4() = default;

	float& operator[] (const enum x_enum);
	float& operator[] (const enum y_enum);
	float& operator[] (const enum z_enum);
	float& operator[] (const enum w_enum);
	float operator[] (const enum x_enum) const;
	float operator[] (const enum y_enum) const;
	float operator[] (const enum z_enum) const;
	float operator[] (const enum w_enum) const;
	float x()const;
	float y()const;
	float z()const;
	float w()const;
	void x(const float x);
	void y(const float y);
	void z(const float z);
	void w(const float w);
	void set(const float x, const float y, const float z, const float w);
	void set(const Vec3& v, const float w);
	void set(const Vec2& inVec2);
	void set(const Vec3& inVec3);
	void set(const Vec4& inVec4);

	Vec4 operator + () const;
	Vec4 operator + (const Vec4& inVec4) const;
	Vec4& operator += (const Vec4& inVec4);

	Vec4 operator - () const;
	Vec4 operator - (const Vec4& inVec4) const;
	Vec4& operator -= (const Vec4& inVec4);

	Vec4 operator * (const float scale) const;
	friend Vec4 operator * (const float scale, const Vec4& inVec4);
	Vec4& operator *= (const float scale);

	Vec4 operator * (const Mat4& m) const;
	Vec4& operator *= (const Mat4& m);

	Vec4& norm();
	Vec4 getNorm() const;
	float dot(const Vec4& inVec4) const;
	Vec4Proxy len() const;

	bool isEqual(const Vec4& inVec4, const float epsilon = MATH_TOLERANCE) const;
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
			float _vz;
			float _vw;
		};
	};
};

#endif
