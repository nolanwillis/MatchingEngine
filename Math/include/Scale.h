#ifndef MATH_SCALE_H
#define MATH_SCALE_H

#include "Enum.h"
#include "Mat4.h"

class Quat;
class Rot;
class Trans;
class Vec3;

class Scale final : public Mat4
{
public:
	Scale();
	Scale(const enum Identity_enum);
	Scale(const float sx, const float sy, const float sz);
	Scale(const float uniformScale);
	Scale(const Vec3& vScale);
	Scale(const Scale& tM) = default;
	Scale& operator = (const Scale& A) = default;
	Scale(Scale&&) = default;
	Scale& operator = (Scale&&) = default;
	~Scale() = default;

	void set(const float sx, const float sy, const float sz);
	void set(const float scale);
	void set(const Vec3& vScale);
	void set(const enum Identity_enum);

	Mat4 operator * (const Mat4& A) const;
	Scale& operator *= (const Mat4& A) = delete;
	Scale operator * (const Scale& A) const;
	Scale& operator *= (const Scale& A);
	Mat4 operator * (const Rot& A) const;
	Scale& operator *= (const Rot& A) = delete;
	Mat4 operator * (const Trans& A) const;
	Scale& operator *= (const Trans& A) = delete;
	Mat4 operator * (const Quat& q) const;
};

#endif
