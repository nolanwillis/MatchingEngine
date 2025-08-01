#ifndef MATH_ROT_H
#define MATH_ROT_H

#include "Enum.h"
#include "Mat4.h"

class Quat;
class Scale;
class Trans;
class Vec3;

class Rot final : public Mat4
{
public:
	Rot();
	Rot(const enum Identity_enum);
	Rot(const Rot1 type, const float angle_radians);
	Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);
	Rot(const Axis mode, const Vec3& vAxis, const float angle_radians);
	Rot(const Orient type, const Vec3& dof, const Vec3& up);
	explicit Rot(const Quat& q);
	Rot& operator = (const Rot& A) = default;
	Rot(const Rot& tM) = default;
	Rot(Rot&&) = default;
	Rot& operator = (Rot&&) = default;
	Rot& operator = (const Quat& q);
	~Rot() = default;

	void set(const enum Identity_enum);
	void set(const Rot& rot);
	void set(const Rot1 type, const float angle);
	void set(const Rot3 mode, const float angle_0_radians, const float angle_1_radians,
		const float angle_2_radians);
	void set(const Axis mode, const Vec3& vAxis, const float angle_radians);
	void set(const Orient, const Vec3& dof, const Vec3& up);
	void set(const Quat& qIn);

	Mat4 operator * (const Mat4& A) const;
	Rot& operator *= (const Mat4& A) = delete;
	Mat4 operator * (const Scale& A) const;
	Rot& operator *= (const Scale& A) = delete;
	Rot operator * (const Rot& A) const;
	Rot& operator *= (const Rot& A);
	Mat4 operator * (const Trans& A) const;
	Rot& operator *= (const Trans& A) = delete;
	Rot operator * (const Quat& q) const;
	Rot& operator *= (const Quat& q);
};

#endif
