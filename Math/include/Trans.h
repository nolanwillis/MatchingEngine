#ifndef MATH_TRANS_H
#define MATH_TRANS_H

#include "Enum.h"
#include "Mat4.h"

class Quat;
class Rot;
class Scale;
class Vec3;
class Vec4;

class Trans final : public Mat4
{
public:
	Trans();
	Trans(const enum Identity_enum);
	Trans(const float tx, const float ty, const float tz);
	Trans(const Vec3& vTrans);
	Trans(const Vec4& vTrans);
	Trans(const Trans& tM) = default;
	Trans& operator = (const Trans& A) = default;
	Trans(Trans&&) = default;
	Trans& operator = (Trans&&) = default;
	~Trans() = default;

	void set(const float tx, const float ty, const float tz);
	void set(const Vec3& vTrans);
	void set(const enum Identity_enum);

	Mat4 operator * (const Mat4& A) const;
	Trans& operator *= (const Mat4& A) = delete;
	Mat4 operator * (const Scale& A) const;
	Trans& operator *= (const Scale& A) = delete;
	Mat4 operator * (const Rot& A) const;
	Trans& operator *= (const Rot& A) = delete;
	Trans operator * (const Trans& A) const;
	Trans& operator *= (const Trans& A);
	Mat4 operator * (const Quat& q) const;
};

#endif
