#include "Mat3.h"
#include "Mat4.h"
#include "Quat.h"

#include <cstdio>

Mat3::Mat3()
{
	_m0 = 0.0f;
	_m1 = 0.0f;
	_m2 = 0.0f;
	_m3 = 0.0f;
	_m4 = 0.0f; 
	_m5 = 0.0f;
	_m6 = 0.0f;
	_m7 = 0.0f;
	_m8 = 0.0f;
	_m9 = 0.0f;
	_m10 = 0.0f;
	_m11 = 0.0f;
	_m12 = 0.0f;
	_m13 = 0.0f;
	_m14 = 0.0f;
	_m15 = 0.0f;
}
Mat3::Mat3(const Vec3& tV0, const Vec3& tV1, const Vec3& tV2)
{
	this->_v0._vx = tV0._vx;
	this->_v0._vy = tV0._vy;
	this->_v0._vz = tV0._vz;
	this->_v1._vx = tV1._vx;
	this->_v1._vy = tV1._vy;
	this->_v1._vz = tV1._vz;
	this->_v2._vx = tV2._vx;
	this->_v2._vy = tV2._vy;
	this->_v2._vz = tV2._vz;
}
Mat3::Mat3(const Quat& q)
{
	float qx = q._qx;
	float qy = q._qy;
	float qz = q._qz;
	float qw = q._qw;

	this->_m0 = 1.0f - (2.0f * ((qy * qy) + (qz * qz)));
	this->_m1 = 2.0f * ((qx * qy) + (qw * qz));
	this->_m2 = 2.0f * ((qx * qz) - (qw * qy));
	this->_m3 = 0.0f;
	this->_m4 = 2.0f * ((qx * qy) - (qw * qz));
	this->_m5 = 1.0f - (2.0f * ((qx * qx) + (qz * qz)));
	this->_m6 = 2.0f * ((qy * qz) + (qw * qx));
	this->_m7 = 0.0f;
	this->_m8 = 2.0f * ((qx * qz) + (qw * qy));
	this->_m9 = 2.0f * ((qy * qz) - (qw * qx));
	this->_m10 = 1.0f - (2.0f * ((qx * qx) + (qy * qy)));
	this->_m11 = 0.0f;
	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;
	this->_m15 = 1.0f;
}
Mat3::Mat3(const enum Identity_enum)
{
	_m0 = 1.0f;
	_m1 = 0.0f;
	_m2 = 0.0f;
	_m3 = 0.0f;
	_m4 = 0.0f;
	_m5 = 1.0f;
	_m6 = 0.0f;
	_m7 = 0.0f;
	_m8 = 0.0f;
	_m9 = 0.0f;
	_m10 = 1.0f;
	_m11 = 0.0f;
	_m12 = 0.0f;
	_m13 = 0.0f;
	_m14 = 0.0f;
	_m15 = 1.0f;
}
Mat3::Mat3(const Mat4& m)
{
	this->_m0 = m._m0;
	this->_m1 = m._m1;
	this->_m2 = m._m2;
	this->_m3 = m._m3;
	this->_m4 = m._m4;
	this->_m5 = m._m5;
	this->_m6 = m._m6;
	this->_m7 = m._m7;
	this->_m8 = m._m8;
	this->_m9 = m._m9;
	this->_m10 = m._m10;
	this->_m11 = m._m11;
	this->_m12 = m._m12;
	this->_m13 = m._m13;
	this->_m14 = m._m14;
	this->_m15 = m._m15;
}

Mat3::Mat3(const Mat3& tM)
{
	this->_v0 = tM._v0;
	this->_v1 = tM._v1;
	this->_v2 = tM._v2;
}
Mat3& Mat3::operator=(const Mat3& A)
{
	this->_v0 = A._v0;
	this->_v1 = A._v1;
	this->_v2 = A._v2;
	return *this;
}

float& Mat3::operator[] (const enum m0_enum)
{
	return _m0;
}
float& Mat3::operator[] (const enum m1_enum)
{
	return _m1;
}
float& Mat3::operator[] (const enum m2_enum)
{
	return _m2;
}
float& Mat3::operator[] (const enum m4_enum)
{
	return _m4;
}
float& Mat3::operator[] (const enum m5_enum)
{
	return _m5;
}
float& Mat3::operator[] (const enum m6_enum)
{
	return _m6;
}
float& Mat3::operator[] (const enum m8_enum)
{
	return _m8;
}
float& Mat3::operator[] (const enum m9_enum)
{
	return _m9;
}
float& Mat3::operator[] (const enum m10_enum)
{
	return _m10;
}

float Mat3::operator[] (const enum m0_enum) const
{
	return _m0;
}
float Mat3::operator[] (const enum m1_enum) const
{
	return _m1;
}
float Mat3::operator[] (const enum m2_enum) const
{
	return _m2;
}
float Mat3::operator[] (const enum m4_enum) const
{
	return _m4;
}
float Mat3::operator[] (const enum m5_enum) const
{
	return _m5;
}
float Mat3::operator[] (const enum m6_enum) const
{
	return _m6;
}
float Mat3::operator[] (const enum m8_enum) const
{
	return _m8;
}
float Mat3::operator[] (const enum m9_enum) const
{
	return _m9;
}
float Mat3::operator[] (const enum m10_enum) const
{
	return _m10;
}

void Mat3::set(const Mat3& mIn)
{
	this->_v0 = mIn._v0;
	this->_v1 = mIn._v1;
	this->_v2 = mIn._v2;
}
void Mat3::set(const Vec3& V0, const Vec3& V1, const Vec3& V2)
{
	this->_m0 = V0._vx;
	this->_m1 = V0._vy;
	this->_m2 = V0._vz;
	this->_m4 = V1._vx;
	this->_m5 = V1._vy;
	this->_m6 = V1._vz;
	this->_m8 = V2._vx;
	this->_m9 = V2._vy;
	this->_m10 = V2._vz;
}
void Mat3::set(const enum Identity_enum)
{
	_m0 = 1;
	_m1 = 0;
	_m2 = 0;
	_m4 = 0;
	_m5 = 1;
	_m6 = 0;
	_m8 = 0;
	_m9 = 0;
	_m10 = 1;
}
void Mat3::set(const Row3 type, const Vec3& V)
{
	switch (type)
	{
	case Row3::i0:
		this->_m0 = V._vx;
		this->_m1 = V._vy;
		this->_m2 = V._vz;
		break;
	case Row3::i1:
		this->_m4 = V._vx;
		this->_m5 = V._vy;
		this->_m6 = V._vz;
		break;
	case Row3::i2:
		this->_m8 = V._vx;
		this->_m9 = V._vy;
		this->_m10 = V._vz;
		break;
	default:
		break;
	}
}
Vec3 Mat3::get(const Row3 type) const
{
	switch (type)
	{
	case Row3::i0:
		return Vec3(_v0._vx, _v0._vy, _v0._vz);
	case Row3::i1:
		return Vec3(_v1._vx, _v1._vy, _v1._vz);
	case Row3::i2:
		return Vec3(_v2._vx, _v2._vy, _v2._vz);
	default:
		break;
	}
	return Vec3(0, 0, 0);
}

void Mat3::m0(const float v)
{
	this->_m0 = v;
}
void Mat3::m1(const float v)
{
	this->_m1 = v;
}
void Mat3::m2(const float v)
{
	this->_m2 = v;
}
void Mat3::m4(const float v)
{
	this->_m4 = v;
}
void Mat3::m5(const float v)
{
	this->_m5 = v;
}
void Mat3::m6(const float v)
{
	this->_m6 = v;
}
void Mat3::m8(const float v)
{
	this->_m8 = v;
}
void Mat3::m9(const float v)
{
	this->_m9 = v;
}
void Mat3::m10(const float v)
{
	this->_m10 = v;
}

float Mat3::m0() const
{
	return this->_m0;
}
float Mat3::m1() const
{
	return this->_m1;
}
float Mat3::m2() const
{
	return this->_m2;
}
float Mat3::m4() const
{
	return this->_m4;
}
float Mat3::m5() const
{
	return this->_m5;
}
float Mat3::m6() const
{
	return this->_m6;
}
float Mat3::m8() const
{
	return this->_m8;
}
float Mat3::m9() const
{
	return this->_m9;
}
float Mat3::m10() const
{
	return this->_m10;
}

Mat3 Mat3::operator+(void) const
{
	Vec3 v0(this->_m0, this->_m1, this->_m2);
	Vec3 v1(this->_m4, this->_m5, this->_m6);
	Vec3 v2(this->_m8, this->_m9, this->_m10);
	return Mat3(+v0, +v1, +v2);
}
Mat3 Mat3::operator+(const Mat3& A) const
{
	Vec3 v0(this->_m0 + A._m0, this->_m1 + A._m1, this->_m2 + A._m2);
	Vec3 v1(this->_m4 + A._m4, this->_m5 + A._m5, this->_m6 + A._m6);
	Vec3 v2(this->_m8 + A._m8, this->_m9 + A._m9, this->_m10 + A._m10);
	return Mat3(v0, v1, v2);
}
Mat3& Mat3::operator+=(const Mat3& A)
{
	_v0 += A._v0;
	_v1 += A._v1;
	_v2 += A._v2;
	return *this;
}

Mat3 Mat3::operator-(void) const
{
	Vec3 v0(this->_m0, this->_m1, this->_m2);
	Vec3 v1(this->_m4, this->_m5, this->_m6);
	Vec3 v2(this->_m8, this->_m9, this->_m10);
	return Mat3(-v0, -v1, -v2);
}
Mat3 Mat3::operator-(const Mat3& A) const
{
	Vec3 v0(this->_m0 - A._m0, this->_m1 - A._m1, this->_m2 - A._m2);
	Vec3 v1(this->_m4 - A._m4, this->_m5 - A._m5, this->_m6 - A._m6);
	Vec3 v2(this->_m8 - A._m8, this->_m9 - A._m9, this->_m10 - A._m10);
	return Mat3(v0, v1, v2);
}
Mat3& Mat3::operator-=(const Mat3& A)
{
	this->_v0 -= A._v0;
	this->_v1 -= A._v1;
	this->_v2 -= A._v2;
	return *this;
}

Mat3 Mat3::operator*(const float scale) const
{
	Vec3 v0(this->_m0 * scale, this->_m1 * scale, this->_m2 * scale);
	Vec3 v1(this->_m4 * scale, this->_m5 * scale, this->_m6 * scale);
	Vec3 v2(this->_m8 * scale, this->_m9 * scale, this->_m10 * scale);
	return Mat3(v0, v1, v2);
}
Mat3& Mat3::operator*=(const float scale)
{
	this->_v0 *= scale;
	this->_v1 *= scale;
	this->_v2 *= scale;
	this->_v3 *= scale;
	return *this;
}
Mat3 operator*(const float scale, const Mat3& A)
{
	Vec3 v0(A._m0 * scale, A._m1 * scale, A._m2 * scale);
	Vec3 v1(A._m4 * scale, A._m5 * scale, A._m6 * scale);
	Vec3 v2(A._m8 * scale, A._m9 * scale, A._m10 * scale);
	return Mat3(v0, v1, v2);
}

Mat3 Mat3::operator*(const Mat3& A) const
{
	Mat3 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10);
	return m;
}
Mat3& Mat3::operator*=(const Mat3& A)
{
	float m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8);
	float m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9);
	float m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10);
	float m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8);
	float m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9);
	float m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10);
	float m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8);
	float m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9);
	float m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10);
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	return *this;
}

float Mat3::det() const
{
	return (_m0 * ((_m5 * _m10) - (_m6 * _m9))) - (_m1 * ((_m4 * _m10) - (_m6 * _m8))) +
		(_m2 * ((_m4 * _m9) - (_m5 * _m8)));
}
Mat3& Mat3::T(void)
{
	float temp = _m4;
	this->_m4 = _m1;
	this->_m1 = temp;
	temp = _m2;
	this->_m2 = _m8;
	this->_m8 = temp;
	temp = _m6;
	this->_m6 = _m9;
	this->_m9 = temp;

	return *this;
}
Mat3 Mat3::getT(void) const
{
	Vec3 v0(_m0, _m4, _m8);
	Vec3 v1(_m1, _m5, _m9);
	Vec3 v2(_m2, _m6, _m10);
	return Mat3(v0, v1, v2);
}
Mat3 Mat3::getInv(void) const
{
	float det = this->det();
	float m0 = ((_m5 * _m10) - (_m6 * _m9)) / det;
	float m1 = ((_m2 * _m9) - (_m1 * _m10)) / det;
	float m2 = ((_m1 * _m6) - (_m2 * _m5)) / det;
	float m4 = ((_m6 * _m8) - (_m4 * _m10)) / det;
	float m5 = ((_m0 * _m10) - (_m2 * _m8)) / det;
	float m6 = ((_m2 * _m4) - (_m0 * _m6)) / det;
	float m8 = ((_m4 * _m9) - (_m5 * _m8)) / det;
	float m9 = ((_m1 * _m8) - (_m0 * _m9)) / det;
	float m10 = ((_m0 * _m5) - (_m1 * _m4)) / det;
	Mat3 m;
	m._m0 = m0;
	m._m1 = m1;
	m._m2 = m2;
	m._m4 = m4;
	m._m5 = m5;
	m._m6 = m6;
	m._m8 = m8;
	m._m9 = m9;
	m._m10 = m10;
	return m;
}
Mat3& Mat3::inv(void)
{
	float det = this->det();
	float m0 = ((_m5 * _m10) - (_m6 * _m9)) / det;
	float m1 = ((_m2 * _m9) - (_m1 * _m10)) / det;
	float m2 = ((_m1 * _m6) - (_m2 * _m5)) / det;
	float m4 = ((_m6 * _m8) - (_m4 * _m10)) / det;
	float m5 = ((_m0 * _m10) - (_m2 * _m8)) / det;
	float m6 = ((_m2 * _m4) - (_m0 * _m6)) / det;
	float m8 = ((_m4 * _m9) - (_m5 * _m8)) / det;
	float m9 = ((_m1 * _m8) - (_m0 * _m9)) / det;
	float m10 = ((_m0 * _m5) - (_m1 * _m4)) / det;
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	return *this;
}

bool Mat3::isEqual(const Mat3& A, const float epsilon) const
{
	return
		(
			this->_m0 <= A._m0 + epsilon && this->_m0 >= A._m0 - epsilon &&
			this->_m1 <= A._m1 + epsilon && this->_m1 >= A._m1 - epsilon &&
			this->_m2 <= A._m2 + epsilon && this->_m2 >= A._m2 - epsilon &&
			this->_m4 <= A._m4 + epsilon && this->_m4 >= A._m4 - epsilon &&
			this->_m5 <= A._m5 + epsilon && this->_m5 >= A._m5 - epsilon &&
			this->_m6 <= A._m6 + epsilon && this->_m6 >= A._m6 - epsilon &&
			this->_m8 <= A._m8 + epsilon && this->_m8 >= A._m8 - epsilon &&
			this->_m9 <= A._m9 + epsilon && this->_m9 >= A._m9 - epsilon &&
			this->_m10 <= A._m10 + epsilon && this->_m10 >= A._m10 - epsilon
			);
}
bool Mat3::isIdentity(const float epsilon) const
{
	return
		(
			this->_m0 <= 1.0f + epsilon && this->_m0 >= 1.0f - epsilon &&
			this->_m1 <= epsilon && this->_m1 >= -epsilon &&
			this->_m2 <= epsilon && this->_m2 >= -epsilon &&
			this->_m4 <= epsilon && this->_m4 >= -epsilon &&
			this->_m5 <= 1.0f + epsilon && this->_m5 >= 1.0f - epsilon &&
			this->_m6 <= epsilon && this->_m6 >= -epsilon &&
			this->_m8 <= epsilon && this->_m8 >= -epsilon &&
			this->_m9 <= epsilon && this->_m9 >= -epsilon &&
			this->_m10 <= 1.0f + epsilon && this->_m10 >= 1.0f - epsilon
			);
}

void Mat3::Print(const char* pName) const
{
	std::printf("%s:\n", pName);
	std::printf("|%.4f %.4f %.4f|\n", _m0, _m1, _m2);
	std::printf("|%.4f %.4f %.4f|\n", _m4, _m5, _m6);
	std::printf("|%.4f %.4f %.4f|\n", _m8, _m9, _m10);
}

