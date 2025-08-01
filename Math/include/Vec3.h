#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "Constants.h"
#include "Enum.h"
#include "Vec3Proxy.h"

// SIMD includes.
#include <xmmintrin.h>
#include <smmintrin.h> 

class Mat3;
class Quat;
class Vec2;
class Vec4;

class Vec3 
{
public:
	friend class Mat3;
	friend class Mat4;
	friend class Scale;
	friend class Trans;
	friend class Vec2;
	friend class Vec4;

	Vec3();
	Vec3(const float x, const float y, const float z);
	explicit Vec3(const Vec2& rhs);
	Vec3(const Vec3& rhs);
	explicit Vec3(const Vec4& rhs);
	Vec3& operator=(const Vec2& rhs);
	Vec3& operator=(const Vec3& rhs);
	Vec3& operator=(const Vec4& rhs);
	Vec3(Vec3&& rhs) = default;
	Vec3& operator = (Vec3&& rhs) = default;
	~Vec3() = default;

	float& operator[] (const enum x_enum);
	float& operator[] (const enum y_enum);
	float& operator[] (const enum z_enum);
	float operator[] (const enum x_enum) const;
	float operator[] (const enum y_enum) const;
	float operator[] (const enum z_enum) const;
	float x() const;
	float y() const;
	float z() const;
	void x(const float x);
	void y(const float y);
	void z(const float z);
	void set(const float x, const float y, const float z);
	void set(const Vec2& inVec2);
	void set(const Vec3& inVec3);
	void set(const Vec4& inVec4);

	Vec3 operator + () const;
	Vec3 operator + (const Vec3& inVec3) const;
	Vec3& operator += (const Vec3& inVec3);

	Vec3 operator - () const;
	Vec3 operator - (const Vec3& inVec3) const;
	Vec3& operator -= (const Vec3& inVec3);

	Vec3 operator * (const float scale) const;
	friend Vec3 operator * (const float scale, const Vec3& inVec3);
	Vec3& operator *= (const float scale);
	Vec3 operator * (const Mat3& m) const;
	Vec3& operator *= (const Mat3& m);
	Vec3 operator * (const Quat& q) const;
	Vec3& operator *= (const Quat& q);

	Vec3& norm();
	Vec3 getNorm() const;
	float dot(const Vec3& vIn) const;
	Vec3 cross(const Vec3& vIn) const;
	Vec3Proxy len() const;
	float getAngle(const Vec3& vIn) const;

	bool isEqual(const Vec3& v, const float epsilon = MATH_TOLERANCE) const;
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
		};
	};
};

#endif
