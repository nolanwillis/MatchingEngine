#include "Trans.h"
#include "Rot.h"
#include "Scale.h"
#include "Vec3.h"

Trans::Trans()
{
	this->_m0 = 1.0f;
	this->_m5 = 1.0f;
	this->_m10 = 1.0f;
	this->_m15 = 1.0f;
	this->privSetTransHint(); 
}
Trans::Trans(const enum Identity_enum)
{
	this->_m0 = 1.0f;
	this->_m5 = 1.0f;
	this->_m10 = 1.0f;
	this->_m15 = 1.0f;
	this->privSetTransHint();
}
Trans::Trans(const float tx, const float ty, const float tz)
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
	this->_m12 = tx;
	this->_m13 = ty;
	this->_m14 = tz;
	_m15 = 1.0f;
	this->privSetTransHint();
}
Trans::Trans(const Vec3& vTrans)
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
	this->_m12 = vTrans._vx;
	this->_m13 = vTrans._vy;
	this->_m14 = vTrans._vz;
	_m15 = 1.0f;
	this->privSetTransHint();
}
Trans::Trans(const Vec4& vTrans)
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
	this->_m12 = vTrans._vx;
	this->_m13 = vTrans._vy;
	this->_m14 = vTrans._vz;
	_m15 = 1.0f;
	this->privSetTransHint();
}

void Trans::set(const float tx, const float ty, const float tz)
{
	this->_m12 = tx;
	this->_m13 = ty;
	this->_m14 = tz;
}
void Trans::set(const Vec3& vTrans)
{
	this->_m12 = vTrans._vx;
	this->_m13 = vTrans._vy;
	this->_m14 = vTrans._vz;
}
void Trans::set(const enum Identity_enum)
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
	this->privSetTransHint();
}

Mat4 Trans::operator*(const Mat4& A) const
{
	// Store A's inverse hint.
	Hint AHint = A.privGetHint();
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
	// Apply A's inverse hint combined with this matrix's hint. 
	m.privSetNewHint(AHint, this->privGetHint());
	return m;
}
Mat4 Trans::operator*(const Scale& A) const
{
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
	m.privSetTransHint();
	return m;
}
Mat4 Trans::operator*(const Rot& A) const
{
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
	m.privSetTransHint();
	return m;
}
Trans Trans::operator*(const Trans& A) const
{
	Trans m = A;
	m.m12(this->_m12 + A._m12);
	m.m13(this->_m13 + A._m13);
	m.m14(this->_m14 + A._m14);
	m.privSetTransHint();
	return m;
}
Trans& Trans::operator*=(const Trans& A)
{
	this->_m12 += A._m12;
	this->_m13 += A._m13;
	this->_m14 += A._m14;
	return *this;
}
Mat4 Trans::operator*(const Quat& q) const
{
	return *this * Mat4(q);
}
