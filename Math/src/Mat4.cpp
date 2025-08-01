#include "Mat4.h"
#include "Mat3.h"
#include "Quat.h"
#include "Scale.h"
#include "Rot.h"
#include "Trans.h"
#include "Util.h"

#include <cstdio>

Mat4::Mat4()
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
Mat4::Mat4(const enum Identity_enum)
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
Mat4::Mat4(const Vec4& tV0, const Vec4& tV1, const Vec4& tV2, const Vec4& tV3)
{
	this->_v0 = tV0;
	this->_v1 = tV1;
	this->_v2 = tV2;
	this->_v3 = tV3;
}
Mat4::Mat4(const Quat& q)
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
Mat4::Mat4(const Mat4& m)
{
	this->_v0 = m._v0;
	this->_v1 = m._v1;
	this->_v2 = m._v2;
	this->_v3 = m._v3;
}
Mat4& Mat4::operator=(const Mat4& m)
{
	this->_v0 = m._v0;
	this->_v1 = m._v1;
	this->_v2 = m._v2;
	this->_v3 = m._v3;
	return *this;
}

Mat4Proxy Mat4::operator[] (const enum m0_enum)
{
	return Mat4Proxy(*this, _m0);
}
Mat4Proxy Mat4::operator[] (const enum m1_enum)
{
	return Mat4Proxy(*this, _m1);
}
Mat4Proxy Mat4::operator[] (const enum m2_enum)
{
	return Mat4Proxy(*this, _m2);
}
Mat4Proxy Mat4::operator[] (const enum m3_enum)
{
	return Mat4Proxy(*this, _m3);
}
Mat4Proxy Mat4::operator[] (const enum m4_enum)
{
	return Mat4Proxy(*this, _m4);
}
Mat4Proxy Mat4::operator[] (const enum m5_enum)
{
	return Mat4Proxy(*this, _m5);
}
Mat4Proxy Mat4::operator[] (const enum m6_enum)
{
	return Mat4Proxy(*this, _m6);
}
Mat4Proxy Mat4::operator[] (const enum m7_enum)
{
	return Mat4Proxy(*this, _m7);
}
Mat4Proxy Mat4::operator[] (const enum m8_enum)
{
	return Mat4Proxy(*this, _m8);
}
Mat4Proxy Mat4::operator[] (const enum m9_enum)
{
	return Mat4Proxy(*this, _m9);
}
Mat4Proxy Mat4::operator[] (const enum m10_enum)
{
	return Mat4Proxy(*this, _m10);
}
Mat4Proxy Mat4::operator[] (const enum m11_enum)
{
	return Mat4Proxy(*this, _m11);
}
Mat4Proxy Mat4::operator[] (const enum m12_enum)
{
	return Mat4Proxy(*this, _m12);
}
Mat4Proxy Mat4::operator[] (const enum m13_enum)
{
	return Mat4Proxy(*this, _m13);
}
Mat4Proxy Mat4::operator[] (const enum m14_enum)
{
	return Mat4Proxy(*this, _m14);
}
Mat4Proxy Mat4::operator[] (const enum m15_enum)
{
	return Mat4Proxy(*this, _m15);
}

float Mat4::operator[] (const enum m0_enum) const
{
	return _m0;
}
float Mat4::operator[] (const enum m1_enum) const
{
	return _m1;
}
float Mat4::operator[] (const enum m2_enum) const
{
	return _m2;
}
float Mat4::operator[] (const enum m3_enum) const
{
	return _m3;
}
float Mat4::operator[] (const enum m4_enum) const
{
	return _m4;
}
float Mat4::operator[] (const enum m5_enum) const
{
	return _m5;
}
float Mat4::operator[] (const enum m6_enum) const
{
	return _m6;
}
float Mat4::operator[] (const enum m7_enum) const
{
	return _m7;
}
float Mat4::operator[] (const enum m8_enum) const
{
	return _m8;
}
float Mat4::operator[] (const enum m9_enum) const
{
	return _m9;
}
float Mat4::operator[] (const enum m10_enum) const
{
	return _m10;
}
float Mat4::operator[] (const enum m11_enum) const
{
	return _m11;
}
float Mat4::operator[] (const enum m12_enum) const
{
	return _m12;
}
float Mat4::operator[] (const enum m13_enum) const
{
	return _m13;
}
float Mat4::operator[] (const enum m14_enum) const
{
	return _m14;
}
float Mat4::operator[] (const enum m15_enum) const
{
	return _m15;
}

void Mat4::set(const Mat4& mIn)
{
	this->_v0 = mIn._v0;
	this->_v1 = mIn._v1;
	this->_v2 = mIn._v2;
	this->_v3 = mIn._v3;
}
void Mat4::set(const Vec4& V0, const Vec4& V1, const Vec4& V2, const Vec4& V3)
{
	this->_v0 = V0;
	this->_v1 = V1;
	this->_v2 = V2;
	this->_v3 = V3;
}
void Mat4::set(const enum Identity_enum)
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
	// Save the current hint.
	unsigned int currHint = this->_u_m15 & 0x7;
	_m15 = 1.0f;
	// Re-apply the hint.
	this->_u_m15 |= currHint;
}
void Mat4::set(const Row4 type, const Vec4& V)
{
	switch (type)
	{
	case Row4::i0:
		this->_v0 = V;
		break;
	case Row4::i1:
		this->_v1 = V;
		break;
	case Row4::i2:
		this->_v2 = V;
		break;
	case Row4::i3:
		this->_v3 = V;
		break;
	default:
		break;
	}
	this->privSetGeneralHint();
}
void Mat4::set(const Quat& qIn)
{
	float qx = qIn._qx;
	float qy = qIn._qy;
	float qz = qIn._qz;
	float qw = qIn._qw;

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
Vec4 Mat4::get(const Row4 type) const
{
	switch (type)
	{
	case Row4::i0:
		return this->_v0;
	case Row4::i1:
		return this->_v1;
	case Row4::i2:
		return this->_v2;
	case Row4::i3:
		return this->_v3;
	default:
		break;
	}
	return this->_v0;
}
void Mat4::m0(const float v)
{
	this->_m0 = v;
	this->privSetGeneralHint();
}
void Mat4::m1(const float v)
{
	this->_m1 = v;
	this->privSetGeneralHint();
}
void Mat4::m2(const float v)
{
	this->_m2 = v;
	this->privSetGeneralHint();
}
void Mat4::m3(const float v)
{
	this->_m3 = v;
	this->privSetGeneralHint();
}
void Mat4::m4(const float v)
{
	this->_m4 = v;
	this->privSetGeneralHint();
}
void Mat4::m5(const float v)
{
	this->_m5 = v;
	this->privSetGeneralHint();
}
void Mat4::m6(const float v)
{
	this->_m6 = v;
	this->privSetGeneralHint();
}
void Mat4::m7(const float v)
{
	this->_m7 = v;
	this->privSetGeneralHint();
}
void Mat4::m8(const float v)
{
	this->_m8 = v;
	this->privSetGeneralHint();
}
void Mat4::m9(const float v)
{
	this->_m9 = v;
	this->privSetGeneralHint();
}
void Mat4::m10(const float v)
{
	this->_m10 = v;
	this->privSetGeneralHint();
}
void Mat4::m11(const float v)
{
	this->_m11 = v;
	this->privSetGeneralHint();
}
void Mat4::m12(const float v)
{
	this->_m12 = v;
	this->privSetGeneralHint();
}
void Mat4::m13(const float v)
{
	this->_m13 = v;
	this->privSetGeneralHint();
}
void Mat4::m14(const float v)
{
	this->_m14 = v;
	this->privSetGeneralHint();
}
void Mat4::m15(const float v)
{
	this->_m15 = v;
	this->privSetGeneralHint();
}

float Mat4::m0() const
{
	return this->_m0;
}
float Mat4::m1() const
{
	return this->_m1;
}
float Mat4::m2() const
{
	return this->_m2;
}
float Mat4::m3() const
{
	return this->_m3;
}
float Mat4::m4() const
{
	return this->_m4;
}
float Mat4::m5() const
{
	return this->_m5;
}
float Mat4::m6() const
{
	return this->_m6;
}
float Mat4::m7() const
{
	return this->_m7;
}
float Mat4::m8() const
{
	return this->_m8;
}
float Mat4::m9() const
{
	return this->_m9;
}
float Mat4::m10() const
{
	return this->_m10;
}
float Mat4::m11() const
{
	return this->_m11;
}
float Mat4::m12() const
{
	return this->_m12;
}
float Mat4::m13() const
{
	return this->_m13;
}
float Mat4::m14() const
{
	return this->_m14;
}
float Mat4::m15() const
{
	return this->_m15;
}

float Mat4::det() const
{
	return ((_m0 * ((_m5 * ((_m10 * _m15) - (_m11 * _m14))) - (_m6 * ((_m9 * _m15) - (_m11 * _m13))) + (_m7 * ((_m9 * _m14) - (_m10 * _m13)))))
		- (_m1 * ((_m4 * ((_m10 * _m15) - (_m11 * _m14))) - (_m6 * ((_m8 * _m15) - (_m11 * _m12))) + (_m7 * ((_m8 * _m14) - (_m10 * _m12)))))
		+ (_m2 * ((_m4 * ((_m9 * _m15) - (_m11 * _m13))) - (_m5 * ((_m8 * _m15) - (_m11 * _m12))) + (_m7 * ((_m8 * _m13) - (_m9 * _m12)))))
		- (_m3 * ((_m4 * ((_m9 * _m14) - (_m10 * _m13))) - (_m5 * ((_m8 * _m14) - (_m10 * _m12))) + (_m6 * ((_m8 * _m13) - (_m9 * _m12))))));
}
Mat4& Mat4::T(void)
{
	Vec4 v0(_m0, _m4, _m8, _m12);
	Vec4 v1(_m1, _m5, _m9, _m13);
	Vec4 v2(_m2, _m6, _m10, _m14);
	Vec4 v3(_m3, _m7, _m11, _m15);
	this->_v0 = v0;
	this->_v1 = v1;
	this->_v2 = v2;
	this->_v3 = v3;
	// If we're transposing a rotation * scale matrix set the inverse hint to general.
	if (this->privGetHint() == Mat4::Hint::RotScale)
	{
		this->privSetGeneralHint();
	}
	return *this;
}
Mat4 Mat4::getT(void) const
{
	Mat4 m(*this);
	m._m1 = this->_m4;
	m._m2 = this->_m8;
	m._m3 = this->_m12;
	m._m4 = this->_m1;
	m._m6 = this->_m9;
	m._m7 = this->_m13;
	m._m8 = this->_m2;
	m._m9 = this->_m6;
	m._m11 = this->_m14;
	m._m12 = this->_m3;
	m._m13 = this->_m7;
	m._m14 = this->_m11;
	return m;
}
Mat4 Mat4::getInv(void) const
{
	Hint h = this->privGetHint();
	switch (h)
	{
	case Mat4::Hint::Generalize:
		return GetGeneralInv();
	case Mat4::Hint::Affine:
		return GetAffineInv();
	case Mat4::Hint::Rot:
		return GetRotInv();
	case Mat4::Hint::Scale:
		return GetScaleInv();
	case Mat4::Hint::Trans:
		return GetTransInv();
	case Mat4::Hint::RotScale:
		return GetRotScaleInv();
	case Mat4::Hint::RotTrans:
		return GetRotTransInv();
	case Mat4::Hint::TransScale:
		return GetTransScaleInv();
	default:
		return GetGeneralInv();
	}
}
Mat4& Mat4::inv(void)
{
	Hint h = this->privGetHint();
	switch (h)
	{
	case Mat4::Hint::Generalize:
		GeneralInv();
		break;
	case Mat4::Hint::Affine:
		AffineInv();
		break;
	case Mat4::Hint::Rot:
		RotInv();
		break;
	case Mat4::Hint::Scale:
		ScaleInv();
		break;
	case Mat4::Hint::Trans:
		TransInv();
		break;
	case Mat4::Hint::RotScale:
		RotScaleInv();
		break;
	case Mat4::Hint::RotTrans:
		RotTransInv();
		break;
	case Mat4::Hint::TransScale:
		TransScaleInv();
		break;
	default:
		GeneralInv();
		break;
	}
	return *this;
}

bool Mat4::isEqual(const Mat4& A, const float epsilon) const
{
	return
		(
			this->_m0 <= A._m0 + epsilon && this->_m0 >= A._m0 - epsilon &&
			this->_m1 <= A._m1 + epsilon && this->_m1 >= A._m1 - epsilon &&
			this->_m2 <= A._m2 + epsilon && this->_m2 >= A._m2 - epsilon &&
			this->_m3 <= A._m3 + epsilon && this->_m3 >= A._m3 - epsilon &&
			this->_m4 <= A._m4 + epsilon && this->_m4 >= A._m4 - epsilon &&
			this->_m5 <= A._m5 + epsilon && this->_m5 >= A._m5 - epsilon &&
			this->_m6 <= A._m6 + epsilon && this->_m6 >= A._m6 - epsilon &&
			this->_m7 <= A._m7 + epsilon && this->_m7 >= A._m7 - epsilon &&
			this->_m8 <= A._m8 + epsilon && this->_m8 >= A._m8 - epsilon &&
			this->_m9 <= A._m9 + epsilon && this->_m9 >= A._m9 - epsilon &&
			this->_m10 <= A._m10 + epsilon && this->_m10 >= A._m10 - epsilon &&
			this->_m11 <= A._m11 + epsilon && this->_m11 >= A._m11 - epsilon &&
			this->_m12 <= A._m12 + epsilon && this->_m12 >= A._m12 - epsilon &&
			this->_m13 <= A._m13 + epsilon && this->_m13 >= A._m13 - epsilon &&
			this->_m14 <= A._m14 + epsilon && this->_m14 >= A._m14 - epsilon &&
			this->_m15 <= A._m15 + epsilon && this->_m15 >= A._m15 - epsilon
			);
}
bool Mat4::isIdentity(const float epsilon) const
{
	return
		(
			this->_m0 <= 1 + epsilon && this->_m0 >= 1 - epsilon &&
			this->_m1 <= epsilon && this->_m1 >= -epsilon &&
			this->_m2 <= epsilon && this->_m2 >= -epsilon &&
			this->_m3 <= epsilon && this->_m3 >= -epsilon &&
			this->_m4 <= epsilon && this->_m4 >= -epsilon &&
			this->_m5 <= 1 + epsilon && this->_m5 >= 1 - epsilon &&
			this->_m6 <= epsilon && this->_m6 >= -epsilon &&
			this->_m7 <= epsilon && this->_m7 >= -epsilon &&
			this->_m8 <= epsilon && this->_m8 >= -epsilon &&
			this->_m9 <= epsilon && this->_m9 >= -epsilon &&
			this->_m10 <= 1 + epsilon && this->_m10 >= 1 - epsilon &&
			this->_m11 <= epsilon && this->_m11 >= -epsilon &&
			this->_m12 <= epsilon && this->_m12 >= -epsilon &&
			this->_m13 <= epsilon && this->_m13 >= -epsilon &&
			this->_m14 <= epsilon && this->_m14 >= -epsilon &&
			this->_m15 <= 1 + epsilon && this->_m15 >= 1 - epsilon
			);
}
bool Mat4::isRotation(const float epsilon) const
{
	Vec3 v0(_m0, _m1, _m2);
	Vec3 v1(_m4, _m5, _m6);
	Vec3 v2(_m8, _m9, _m10);
	float dot00 = v0.dot(v0);
	float dot01 = v0.dot(v1);
	float dot02 = v0.dot(v2);
	float dot10 = v1.dot(v0);
	float dot11 = v1.dot(v1);
	float dot12 = v1.dot(v2);
	float dot20 = v2.dot(v0);
	float dot21 = v2.dot(v1);
	float dot22 = v2.dot(v2);
	bool isOrthogonal = Util::isZero(dot00, epsilon) && Util::isZero(dot01, epsilon) &&
		Util::isZero(dot02, epsilon) && Util::isZero(dot10, epsilon) &&
		Util::isZero(dot11, epsilon) && Util::isZero(dot12, epsilon) &&
		Util::isZero(dot20, epsilon) && Util::isZero(dot21, epsilon) &&
		Util::isZero(dot22, epsilon);
	Mat3 m(v0, v1, v2);
	float mDet = m.det();
	bool is3x3Det1 = Util::isEqual(1.0f, mDet, epsilon);
	bool isHomoCoord = Util::isEqual(_m12, 0.0f, epsilon) &&
		Util::isEqual(_m13, 0.0f, epsilon) && Util::isEqual(_m14, 0.0f, epsilon) &&
		Util::isEqual(_m15, 1.0f, epsilon);
	return isOrthogonal && is3x3Det1 && isHomoCoord;
}

Mat4 Mat4::operator+(void) const
{
	return Mat4(+this->_v0, +this->_v1, +this->_v2, +this->_v3);
}
Mat4 Mat4::operator+(const Mat4& A) const
{
	Vec4 r0 = this->_v0 + A._v0;
	Vec4 r1 = this->_v1 + A._v1;
	Vec4 r2 = this->_v2 + A._v2;
	Vec4 r3 = this->_v3 + A._v3;
	return Mat4(r0, r1, r2, r3);
}
Mat4& Mat4::operator+=(const Mat4& A)
{
	_v0 += A._v0;
	_v1 += A._v1;
	_v2 += A._v2;
	_v3 += A._v3;
	return *this;
}

Mat4 Mat4::operator-(void) const
{
	return Mat4(-_v0, -_v1, -_v2, -_v3);
}
Mat4 Mat4::operator-(const Mat4& A) const
{
	return Mat4
	(
		this->_v0 - A._v0,
		this->_v1 - A._v1,
		this->_v2 - A._v2,
		this->_v3 - A._v3
	);
}
Mat4& Mat4::operator-=(const Mat4& A)
{
	this->_v0 -= A._v0;
	this->_v1 -= A._v1;
	this->_v2 -= A._v2;
	this->_v3 -= A._v3;
	return *this;
}

Mat4 Mat4::operator*(const float scale) const
{
	return Mat4
	(
		this->_v0 * scale,
		this->_v1 * scale,
		this->_v2 * scale,
		this->_v3 * scale
	);
}
Mat4& Mat4::operator*=(const float scale)
{
	this->_v0 *= scale;
	this->_v1 *= scale;
	this->_v2 *= scale;
	this->_v3 *= scale;
	return *this;
}
Mat4 operator*(const float scale, const Mat4& A)
{
	return Mat4
	(
		A._v0 * scale,
		A._v1 * scale,
		A._v2 * scale,
		A._v3 * scale
	);
}
Mat4 Mat4::operator*(const Mat4& A) const
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	m._m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	m._m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	m._m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	m._m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	m._m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	m._m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	m._m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);

	m.privSetNewHint(thisHint, AHint);

	return m;
}
Mat4& Mat4::operator*=(const Mat4& A)
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	float m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	float m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	float m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	float m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	float m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	float m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	float m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	float m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	float m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	float m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	float m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	float m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	float m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	float m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	float m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	float m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m3 = m3;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m7 = m7;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	this->_m11 = m11;
	this->_m12 = m12;
	this->_m13 = m13;
	this->_m14 = m14;
	this->_m15 = m15;

	this->privSetNewHint(thisHint, AHint);

	return *this;
}
Mat4 Mat4::operator*(const Scale& A) const
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	m._m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	m._m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	m._m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	m._m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	m._m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	m._m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	m._m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);

	m.privSetNewHint(thisHint, AHint);

	return m;
}
Mat4& Mat4::operator*=(const Scale& A)
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	float m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	float m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	float m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	float m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	float m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	float m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	float m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	float m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	float m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	float m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	float m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	float m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	float m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	float m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	float m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	float m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m3 = m3;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m7 = m7;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	this->_m11 = m11;
	this->_m12 = m12;
	this->_m13 = m13;
	this->_m14 = m14;
	this->_m15 = m15;

	this->privSetNewHint(thisHint, AHint);

	return *this;
}
Mat4 Mat4::operator*(const Rot& A) const
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	m._m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	m._m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	m._m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	m._m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	m._m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	m._m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	m._m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);

	m.privSetNewHint(thisHint, AHint);

	return m;
}
Mat4& Mat4::operator*=(const Rot& A)
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	float m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	float m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	float m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	float m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	float m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	float m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	float m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	float m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	float m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	float m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	float m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	float m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	float m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	float m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	float m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	float m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m3 = m3;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m7 = m7;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	this->_m11 = m11;
	this->_m12 = m12;
	this->_m13 = m13;
	this->_m14 = m14;
	this->_m15 = m15;

	this->privSetNewHint(thisHint, AHint);

	return *this;
}
Mat4 Mat4::operator*(const Trans& A) const
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	m._m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	m._m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	m._m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	m._m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	m._m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	m._m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	m._m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);

	m.privSetNewHint(thisHint, AHint);

	return m;
}
Mat4& Mat4::operator*=(const Trans& A)
{
	Hint AHint = A.privGetHint();
	Hint thisHint = this->privGetHint();

	float m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + (this->_m3 * A._m12);
	float m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + (this->_m3 * A._m13);
	float m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + (this->_m3 * A._m14);
	float m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + (this->_m3 * A._m15);
	float m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + (this->_m7 * A._m12);
	float m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + (this->_m7 * A._m13);
	float m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + (this->_m7 * A._m14);
	float m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + (this->_m7 * A._m15);
	float m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + (this->_m11 * A._m12);
	float m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + (this->_m11 * A._m13);
	float m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + (this->_m11 * A._m14);
	float m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + (this->_m11 * A._m15);
	float m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + (this->_m15 * A._m12);
	float m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + (this->_m15 * A._m13);
	float m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + (this->_m15 * A._m14);
	float m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + (this->_m15 * A._m15);
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m3 = m3;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m7 = m7;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	this->_m11 = m11;
	this->_m12 = m12;
	this->_m13 = m13;
	this->_m14 = m14;
	this->_m15 = m15;

	this->privSetNewHint(thisHint, AHint);

	return *this;
}
Mat4 Mat4::operator*(const Quat& q) const
{
	return *this * Mat4(q);
}
Mat4 Mat4::operator*=(const Quat& q)
{
	return *this *= Mat4(q);
}

void Mat4::Print(const char* pName) const
{
	std::printf("%s:\n", pName);
	std::printf("|%.4f %.4f %.4f %.4f|\n", _m0, _m1, _m2, _m3);
	std::printf("|%.4f %.4f %.4f %.4f|\n", _m4, _m5, _m6, _m7);
	std::printf("|%.4f %.4f %.4f %.4f|\n", _m8, _m9, _m10, _m11);
	std::printf("|%.4f %.4f %.4f %.4f|\n", _m12, _m13, _m14, _m15);
}

Mat4 Mat4::GetGeneralInv() const
{
	float det = this->det();
	float m0 = (_m5 * (_m10 * _m15 - _m11 * _m14)
		- _m6 * (_m9 * _m15 - _m11 * _m13)
		+ _m7 * (_m9 * _m14 - _m10 * _m13)) / det;
	float m1 = -(_m1 * (_m10 * _m15 - _m11 * _m14)
		- _m2 * (_m9 * _m15 - _m11 * _m13)
		+ _m3 * (_m9 * _m14 - _m10 * _m13)) / det;
	float m2 = (_m1 * (_m6 * _m15 - _m7 * _m14)
		- _m2 * (_m5 * _m15 - _m7 * _m13)
		+ _m3 * (_m5 * _m14 - _m6 * _m13)) / det;
	float m3 = -(_m1 * (_m6 * _m11 - _m7 * _m10)
		- _m2 * (_m5 * _m11 - _m7 * _m9)
		+ _m3 * (_m5 * _m10 - _m6 * _m9)) / det;
	float m4 = -(_m4 * (_m10 * _m15 - _m11 * _m14)
		- _m6 * (_m8 * _m15 - _m11 * _m12)
		+ _m7 * (_m8 * _m14 - _m10 * _m12)) / det;
	float m5 = (_m0 * (_m10 * _m15 - _m11 * _m14)
		- _m2 * (_m8 * _m15 - _m11 * _m12)
		+ _m3 * (_m8 * _m14 - _m10 * _m12)) / det;
	float m6 = -(_m0 * (_m6 * _m15 - _m7 * _m14)
		- _m2 * (_m4 * _m15 - _m7 * _m12)
		+ _m3 * (_m4 * _m14 - _m6 * _m12)) / det;
	float m7 = (_m0 * (_m6 * _m11 - _m7 * _m10)
		- _m2 * (_m4 * _m11 - _m7 * _m8)
		+ _m3 * (_m4 * _m10 - _m6 * _m8)) / det;
	float m8 = (_m4 * (_m9 * _m15 - _m11 * _m13)
		- _m5 * (_m8 * _m15 - _m11 * _m12)
		+ _m7 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m9 = -(_m0 * (_m9 * _m15 - _m11 * _m13)
		- _m1 * (_m8 * _m15 - _m11 * _m12)
		+ _m3 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m10 = (_m0 * (_m5 * _m15 - _m7 * _m13)
		- _m1 * (_m4 * _m15 - _m7 * _m12)
		+ _m3 * (_m4 * _m13 - _m5 * _m12)) / det;
	float m11 = -(_m0 * (_m5 * _m11 - _m7 * _m9)
		- _m1 * (_m4 * _m11 - _m7 * _m8)
		+ _m3 * (_m4 * _m9 - _m5 * _m8)) / det;
	float m12 = -(_m4 * (_m9 * _m14 - _m10 * _m13)
		- _m5 * (_m8 * _m14 - _m10 * _m12)
		+ _m6 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m13 = (_m0 * (_m9 * _m14 - _m10 * _m13)
		- _m1 * (_m8 * _m14 - _m10 * _m12)
		+ _m2 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m14 = -(_m0 * (_m5 * _m14 - _m6 * _m13)
		- _m1 * (_m4 * _m14 - _m6 * _m12)
		+ _m2 * (_m4 * _m13 - _m5 * _m12)) / det;
	float m15 = (_m0 * (_m5 * _m10 - _m6 * _m9)
		- _m1 * (_m4 * _m10 - _m6 * _m8)
		+ _m2 * (_m4 * _m9 - _m5 * _m8)) / det;
	Mat4 m;
	m._m0 = m0;
	m._m1 = m1;
	m._m2 = m2;
	m._m3 = m3;
	m._m4 = m4;
	m._m5 = m5;
	m._m6 = m6;
	m._m7 = m7;
	m._m8 = m8;
	m._m9 = m9;
	m._m10 = m10;
	m._m11 = m11;
	m._m12 = m12;
	m._m13 = m13;
	m._m14 = m14;
	m._m15 = m15;
	return m;
}
Mat4 Mat4::GetAffineInv() const
{
	Mat3 A(*this);
	A.inv();

	Vec3 C(-(this->_v3));
	C *= A;

	return Mat4(A._v0, A._v1, A._v2, Vec4(C._vx, C._vy, C._vz, this->_m15));
}
Mat4 Mat4::GetRotInv() const
{
	Mat3 A(*this);
	A.T();
	return Mat4(A._v0, A._v1, A._v2, A._v3);
}
Mat4 Mat4::GetScaleInv() const
{
	Mat4 m(*this);
	m._m0 = 1.0f / this->_m0;
	m._m5 = 1.0f / this->_m5;
	m._m10 = 1.0f / this->_m10;
	return m;
}
Mat4 Mat4::GetTransInv() const
{
	Mat4 m(*this);
	m.m12(-(this->_m12));
	m.m13(-(this->_m13));
	m.m14(-(this->_m14));
	return m;
}
Mat4 Mat4::GetRotScaleInv() const
{
	Mat3 A(*this);
	A.inv();
	return Mat4(A._v0, A._v1, A._v2, A._v3);
}
Mat4 Mat4::GetRotTransInv() const
{
	Mat3 A(*this);
	A.T();

	Vec3 C(-(this->_v3));
	C *= A;

	return Mat4(A._v0, A._v1, A._v2, Vec4(C._vx, C._vy, C._vz, this->_m15));
}
Mat4 Mat4::GetTransScaleInv() const
{
	Mat4 m;
	m._m0 = 1.0f / this->_m0;
	m._m1 = this->_m1;
	m._m2 = this->_m2;
	m._m3 = this->_m3;
	m._m4 = this->_m4;
	m._m5 = 1.0f / this->_m5;
	m._m6 = this->_m6;
	m._m7 = this->_m7;
	m._m8 = this->_m8;
	m._m9 = this->_m9;
	m._m10 = 1.0f / this->_m10;
	m._m11 = this->_m11;
	m._m12 = -(this->_m12) * m._m0;
	m._m13 = -(this->_m13) * m._m5;
	m._m14 = -(this->_m14) * m._m10;
	m._m15 = this->_m15;
	return m;
}

void Mat4::GeneralInv()
{
	float det = this->det();
	float m0 = (_m5 * (_m10 * _m15 - _m11 * _m14)
		- _m6 * (_m9 * _m15 - _m11 * _m13)
		+ _m7 * (_m9 * _m14 - _m10 * _m13)) / det;
	float m1 = -(_m1 * (_m10 * _m15 - _m11 * _m14)
		- _m2 * (_m9 * _m15 - _m11 * _m13)
		+ _m3 * (_m9 * _m14 - _m10 * _m13)) / det;
	float m2 = (_m1 * (_m6 * _m15 - _m7 * _m14)
		- _m2 * (_m5 * _m15 - _m7 * _m13)
		+ _m3 * (_m5 * _m14 - _m6 * _m13)) / det;
	float m3 = -(_m1 * (_m6 * _m11 - _m7 * _m10)
		- _m2 * (_m5 * _m11 - _m7 * _m9)
		+ _m3 * (_m5 * _m10 - _m6 * _m9)) / det;
	float m4 = -(_m4 * (_m10 * _m15 - _m11 * _m14)
		- _m6 * (_m8 * _m15 - _m11 * _m12)
		+ _m7 * (_m8 * _m14 - _m10 * _m12)) / det;
	float m5 = (_m0 * (_m10 * _m15 - _m11 * _m14)
		- _m2 * (_m8 * _m15 - _m11 * _m12)
		+ _m3 * (_m8 * _m14 - _m10 * _m12)) / det;
	float m6 = -(_m0 * (_m6 * _m15 - _m7 * _m14)
		- _m2 * (_m4 * _m15 - _m7 * _m12)
		+ _m3 * (_m4 * _m14 - _m6 * _m12)) / det;
	float m7 = (_m0 * (_m6 * _m11 - _m7 * _m10)
		- _m2 * (_m4 * _m11 - _m7 * _m8)
		+ _m3 * (_m4 * _m10 - _m6 * _m8)) / det;
	float m8 = (_m4 * (_m9 * _m15 - _m11 * _m13)
		- _m5 * (_m8 * _m15 - _m11 * _m12)
		+ _m7 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m9 = -(_m0 * (_m9 * _m15 - _m11 * _m13)
		- _m1 * (_m8 * _m15 - _m11 * _m12)
		+ _m3 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m10 = (_m0 * (_m5 * _m15 - _m7 * _m13)
		- _m1 * (_m4 * _m15 - _m7 * _m12)
		+ _m3 * (_m4 * _m13 - _m5 * _m12)) / det;
	float m11 = -(_m0 * (_m5 * _m11 - _m7 * _m9)
		- _m1 * (_m4 * _m11 - _m7 * _m8)
		+ _m3 * (_m4 * _m9 - _m5 * _m8)) / det;
	float m12 = -(_m4 * (_m9 * _m14 - _m10 * _m13)
		- _m5 * (_m8 * _m14 - _m10 * _m12)
		+ _m6 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m13 = (_m0 * (_m9 * _m14 - _m10 * _m13)
		- _m1 * (_m8 * _m14 - _m10 * _m12)
		+ _m2 * (_m8 * _m13 - _m9 * _m12)) / det;
	float m14 = -(_m0 * (_m5 * _m14 - _m6 * _m13)
		- _m1 * (_m4 * _m14 - _m6 * _m12)
		+ _m2 * (_m4 * _m13 - _m5 * _m12)) / det;
	float m15 = (_m0 * (_m5 * _m10 - _m6 * _m9)
		- _m1 * (_m4 * _m10 - _m6 * _m8)
		+ _m2 * (_m4 * _m9 - _m5 * _m8)) / det;
	this->_m0 = m0;
	this->_m1 = m1;
	this->_m2 = m2;
	this->_m3 = m3;
	this->_m4 = m4;
	this->_m5 = m5;
	this->_m6 = m6;
	this->_m7 = m7;
	this->_m8 = m8;
	this->_m9 = m9;
	this->_m10 = m10;
	this->_m11 = m11;
	this->_m12 = m12;
	this->_m13 = m13;
	this->_m14 = m14;
	this->_m15 = m15;
}
void Mat4::AffineInv()
{
	Mat3 A(*this);
	A.inv();

	Vec3 C(-(this->_v3));
	C *= A;

	this->_m0 = A._m0;
	this->_m1 = A._m1;
	this->_m2 = A._m2;
	this->_m3 = A._m3;
	this->_m4 = A._m4;
	this->_m5 = A._m5;
	this->_m6 = A._m6;
	this->_m7 = A._m7;
	this->_m8 = A._m8;
	this->_m9 = A._m9;
	this->_m10 = A._m10;
	this->_m11 = A._m11;
	this->_m12 = C._vx;
	this->_m13 = C._vy;
	this->_m14 = C._vz;
}
void Mat4::RotInv()
{
	Mat3 A(*this);
	A.T();

	this->_m0 = A._m0;
	this->_m1 = A._m1;
	this->_m2 = A._m2;
	this->_m4 = A._m4;
	this->_m5 = A._m5;
	this->_m6 = A._m6;
	this->_m8 = A._m8;
	this->_m9 = A._m9;
	this->_m10 = A._m10;
}
void Mat4::ScaleInv()
{
	this->_m0 = 1.0f / this->_m0;
	this->_m5 = 1.0f / this->_m5;
	this->_m10 = 1.0f / this->_m10;
}
void Mat4::TransInv()
{
	this->_m12 = (-(this->_m12));
	this->_m13 = (-(this->_m13));
	this->_m14 = (-(this->_m14));
}
void Mat4::RotScaleInv()
{
	Mat3 A = Mat3(*this);
	A.inv();

	this->_m0 = A._m0;
	this->_m1 = A._m1;
	this->_m2 = A._m2;
	this->_m3 = A._m3;
	this->_m4 = A._m4;
	this->_m5 = A._m5;
	this->_m6 = A._m6;
	this->_m7 = A._m7;
	this->_m8 = A._m8;
	this->_m9 = A._m9;
	this->_m10 = A._m10;
	this->_m11 = A._m11;
}
void Mat4::RotTransInv()
{
	Mat3 A(*this);
	A.T();

	Vec3 C(-(this->_v3));
	C *= A;

	this->_m0 = A._m0;
	this->_m1 = A._m1;
	this->_m2 = A._m2;
	this->_m3 = A._m3;
	this->_m4 = A._m4;
	this->_m5 = A._m5;
	this->_m6 = A._m6;
	this->_m7 = A._m7;
	this->_m8 = A._m8;
	this->_m9 = A._m9;
	this->_m10 = A._m10;
	this->_m11 = A._m11;
	this->_m12 = C._vx;
	this->_m13 = C._vy;
	this->_m14 = C._vz;
}
void Mat4::TransScaleInv()
{
	this->_m0 = 1.0f / this->_m0;
	this->_m5 = 1.0f / this->_m5;
	this->_m10 = 1.0f / this->_m10;
	this->_m12 = -(this->_m12) * this->_m0;
	this->_m13 = -(this->_m13) * this->_m5;
	this->_m14 = -(this->_m14) * this->_m10;
}
