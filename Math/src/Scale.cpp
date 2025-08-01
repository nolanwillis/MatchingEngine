#include "Scale.h"
#include "Trans.h"
#include "Rot.h"
#include "Vec3.h"

Scale::Scale()
{
	this->_m0 = 1.0f;
	this->_m5 = 1.0f;
	this->_m10 = 1.0f;
	this->_m15 = 1.0f;
	this->privSetScaleHint();
}
Scale::Scale(const enum Identity_enum)
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
	this->privSetScaleHint();
}
Scale::Scale(const float sx, const float sy, const float sz)
{
	_m0 = sx;
	_m1 = 0.0f;
	_m2 = 0.0f;
	_m3 = 0.0f;
	_m4 = 0.0f;
	_m5 = sy;
	_m6 = 0.0f;
	_m7 = 0.0f;
	_m8 = 0.0f;
	_m9 = 0.0f;
	_m10 = sz;
	_m11 = 0.0f;
	_m12 = 0.0f;
	_m13 = 0.0f;
	_m14 = 0.0f;
	_m15 = 1.0f;
	this->privSetScaleHint(); 
}
Scale::Scale(const float uniformScale)
{
	_m0 = uniformScale;
	_m1 = 0.0f;
	_m2 = 0.0f;
	_m3 = 0.0f;
	_m4 = 0.0f;
	_m5 = uniformScale;
	_m6 = 0.0f;
	_m7 = 0.0f;
	_m8 = 0.0f;
	_m9 = 0.0f;
	_m10 = uniformScale;
	_m11 = 0.0f;
	_m12 = 0.0f;
	_m13 = 0.0f;
	_m14 = 0.0f;
	_m15 = 1.0f;
	this->privSetScaleHint();
}
Scale::Scale(const Vec3& vScale)
{
	_m0 = vScale._vx;
	_m1 = 0.0f;
	_m2 = 0.0f;
	_m3 = 0.0f;
	_m4 = 0.0f;
	_m5 = vScale._vy;
	_m6 = 0.0f;
	_m7 = 0.0f;
	_m8 = 0.0f;
	_m9 = 0.0f;
	_m10 = vScale._vz;
	_m11 = 0.0f;
	_m12 = 0.0f;
	_m13 = 0.0f;
	_m14 = 0.0f;
	_m15 = 1.0f;
	this->privSetScaleHint();
}

void Scale::set(const float sx, const float sy, const float sz)
{
	_m0 = sx;
	_m5 = sy;
	_m10 = sz;
}
void Scale::set(const float scale)
{
	_m0 = scale;
	_m5 = scale;
	_m10 = scale;
}
void Scale::set(const Vec3& vScale)
{
	_m0 = vScale._vx;
	_m5 = vScale._vy;
	_m10 = vScale._vz;
}
void Scale::set(const enum Identity_enum)
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
	this->privSetScaleHint();
}

Mat4 Scale::operator*(const Mat4& A) const
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
Scale Scale::operator*(const Scale& A) const
{
	Scale m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10);
	m._m15 = 1.0f;
	m.privSetScaleHint();
	return m;
}
Scale& Scale::operator*=(const Scale& A)
{
	float newM0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8);
	float newM1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9);
	float newM2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10);
	float newM4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8);
	float newM5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9);
	float newM6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10);
	float newM8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8);
	float newM9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9);
	float newM10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10);

	this->_m0 = newM0;
	this->_m1 = newM1;
	this->_m2 = newM2;
	this->_m4 = newM4;
	this->_m5 = newM5;
	this->_m6 = newM6;
	this->_m8 = newM8;
	this->_m9 = newM9;
	this->_m10 = newM10;

	return *this;
}
Mat4 Scale::operator*(const Rot& A) const
{
	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10);
	m._m15 = 1.0f;
	m.privSetScaleHint();
	m.privSetRotHint();
	return m;
}
Mat4 Scale::operator*(const Trans& A) const
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
	m.privSetScaleHint();
	m.privSetTransHint();
	return m;
}
Mat4 Scale::operator*(const Quat& q) const
{
	return *this * Mat4(q);
}
