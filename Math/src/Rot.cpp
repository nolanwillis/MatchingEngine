#include "Rot.h"
#include "Quat.h"
#include "Scale.h"
#include "Trans.h"
#include "Trig.h"

Rot::Rot()
{
	this->_m0 = 1.0f;
	this->_m5 = 1.0f;
	this->_m10 = 1.0f;
	this->_m15 = 1.0f;
	this->privSetRotHint();
}
Rot::Rot(const enum Identity_enum)
{
	this->_m0 = 1.0f;
	this->_m5 = 1.0f;
	this->_m10 = 1.0f;
	this->_m15 = 1.0f;
	this->privSetRotHint();
}
Rot::Rot(const Rot1 type, const float angle_radians)
{
	switch (type)
	{
	case Rot1::X:
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = Trig::cos(angle_radians);
		this->_m6 = Trig::sin(angle_radians);
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = -Trig::sin(angle_radians);
		this->_m10 = Trig::cos(angle_radians);
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	case Rot1::Y:
		this->_m0 = Trig::cos(angle_radians);
		this->_m1 = 0.0f;
		this->_m2 = -Trig::sin(angle_radians);
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = Trig::sin(angle_radians);
		this->_m9 = 0.0f;
		this->_m10 = Trig::cos(angle_radians);
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	case Rot1::Z:
		this->_m0 = Trig::cos(angle_radians);
		this->_m1 = Trig::sin(angle_radians);
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = -Trig::sin(angle_radians);
		this->_m5 = Trig::cos(angle_radians);
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	default:
		break;
	}
	this->privSetRotHint();
}
Rot::Rot(const Rot3 mode, const float angle_0_radians, const float angle_1_radians,
	const float angle_2_radians)
{
	Mat4 m;
	switch (mode)
	{
	case Rot3::XYZ:
		m = Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::Z, angle_2_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::XZY:
		m = Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::Y, angle_1_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::YXZ:
		m = Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Z, angle_2_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::YZX:
		m = Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::X, angle_0_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::ZXY:
		m = Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Y, angle_1_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::ZYX:
		m = Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::X, angle_0_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	default:
		break;
	}
	this->_m15 = 1.0f;
	this->privSetRotHint();
}
Rot::Rot(const Axis mode, const Vec3& vAxis, const float angle_radians)
{
	if (mode == Axis::AxisAngle) {}

	const float angle_a = 0.5f * angle_radians;
	float cos_a;
	float sin_a;

	Trig::cossin(cos_a, sin_a, angle_a);

	Vec3 qV = vAxis.getNorm();

	qV *= sin_a;

	Vec4 Q;
	Q[x] = qV[x];
	Q[y] = qV[y];
	Q[z] = qV[z];
	Q[w] = cos_a;

	// this function has been transposed
	float x2, y2, z2;
	float xx, xy, xz;
	float yy, yz, zz;
	float wx, wy, wz;

	// ADD test to make sure that quat is normalized

	x2 = Q[x] + Q[x];
	y2 = Q[y] + Q[y];
	z2 = Q[z] + Q[z];

	xx = Q[x] * x2;
	xy = Q[x] * y2;
	xz = Q[x] * z2;

	yy = Q[y] * y2;
	yz = Q[y] * z2;
	zz = Q[z] * z2;

	wx = Q[w] * x2;
	wy = Q[w] * y2;
	wz = Q[w] * z2;

	this->_m0 = 1.0f - (yy + zz);
	this->_m1 = xy + wz;
	this->_m2 = xz - wy;
	this->_m3 = 0.0f;

	this->_m4 = xy - wz;
	this->_m5 = 1.0f - (xx + zz);
	this->_m6 = yz + wx;
	this->_m7 = 0.0f;

	this->_m8 = xz + wy;
	this->_m9 = yz - wx;
	this->_m10 = 1.0f - (xx + yy);
	this->_m11 = 0.0f;

	this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

	this->_m15 = 1.0f;
	this->privSetRotHint();
}
Rot::Rot(const Orient type, const Vec3& dof, const Vec3& up)
{
	Vec3 zAxis = dof;
	zAxis.norm();

	Vec3 xAxis = up.cross(zAxis);
	xAxis.norm();

	Vec3 yAxis = (zAxis.cross(xAxis));
	yAxis.norm();

	if (type == Orient::WorldToLocal) {
		_m0 = xAxis.x(); _m1 = yAxis.x(); _m2 = zAxis.x(); _m3 = 0.0f;
		_m4 = xAxis.y(); _m5 = yAxis.y(); _m6 = zAxis.y(); _m7 = 0.0f;
		_m8 = xAxis.z(); _m9 = yAxis.z(); _m10 = zAxis.z(); _m11 = 0.0f;
	}
	else {
		_m0 = xAxis.x(); _m1 = xAxis.y(); _m2 = xAxis.z(); _m3 = 0.0f;
		_m4 = yAxis.x(); _m5 = yAxis.y(); _m6 = yAxis.z(); _m7 = 0.0f;
		_m8 = zAxis.x(); _m9 = zAxis.y(); _m10 = zAxis.z(); _m11 = 0.0f;
	}

	_m12 = 0.0f; _m13 = 0.0f; _m14 = 0.0f; _m15 = 1.0f;

	this->privSetRotHint();
}
Rot::Rot(const Quat& q)
	: Mat4(q)
{}

void Rot::set(const enum Identity_enum)
{
	this->_m0 = 1.0f;
	this->_m1 = 0.0f;
	this->_m2 = 0.0f;
	this->_m3 = 0.0f;
	this->_m4 = 0.0f;
	this->_m5 = 1.0f;
	this->_m6 = 0.0f;
	this->_m7 = 0.0f;
	this->_m8 = 0.0f;
	this->_m9 = 0.0f;
	this->_m10 = 1.0f;
	this->_m11 = 0.0f;
	this->_m12 = 0.0f;
	this->_m13 = 0.0f;
	this->_m14 = 0.0f;
	this->_m15 = 1.0f;
}
Rot& Rot::operator=(const Quat& q)
{
	*this = Rot(q);
	return *this;
}
void Rot::set(const Rot& rot)
{
	this->_m0 = rot._m0;
	this->_m1 = rot._m1;
	this->_m2 = rot._m2;
	this->_m3 = rot._m3;
	this->_m4 = rot._m4;
	this->_m5 = rot._m5;
	this->_m6 = rot._m6;
	this->_m7 = rot._m7;
	this->_m8 = rot._m8;
	this->_m9 = rot._m9;
	this->_m10 = rot._m10;
	this->_m11 = rot._m11;
	this->_m12 = rot._m12;
	this->_m13 = rot._m13;
	this->_m14 = rot._m14;
	this->_m15 = rot._m15;
}
void Rot::set(const Rot1 type, const float angle_radians)
{
	switch (type)
	{
	case Rot1::X:
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = Trig::cos(angle_radians);
		this->_m6 = Trig::sin(angle_radians);
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = -Trig::sin(angle_radians);
		this->_m10 = Trig::cos(angle_radians);
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	case Rot1::Y:
		this->_m0 = Trig::cos(angle_radians);
		this->_m1 = 0.0f;
		this->_m2 = -Trig::sin(angle_radians);
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = Trig::sin(angle_radians);
		this->_m9 = 0.0f;
		this->_m10 = Trig::cos(angle_radians);
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	case Rot1::Z:
		this->_m0 = Trig::cos(angle_radians);
		this->_m1 = Trig::sin(angle_radians);
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = -Trig::sin(angle_radians);
		this->_m5 = Trig::cos(angle_radians);
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
		break;
	default:
		break;
	}
	this->privSetRotHint();
}
void Rot::set(const Rot3 mode, const float angle_0_radians, const float angle_1_radians,
	const float angle_2_radians)
{
	Mat4 m;
	switch (mode)
	{
	case Rot3::XYZ:
		m = Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::Z, angle_2_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::XZY:
		m = Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::Y, angle_1_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::YXZ:
		m = Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Z, angle_2_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::YZX:
		m = Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::X, angle_0_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::ZXY:
		m = Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::X, angle_0_radians) * Rot(Rot1::Y, angle_1_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	case Rot3::ZYX:
		m = Rot(Rot1::Z, angle_2_radians) * Rot(Rot1::Y, angle_1_radians) * Rot(Rot1::X, angle_0_radians);
		this->_v0 = m._v0;
		this->_v1 = m._v1;
		this->_v2 = m._v2;
		this->_v3 = m._v3;
		break;
	default:
		break;
	}

	this->privSetRotHint();
}
void Rot::set(const Axis mode, const Vec3& vAxis, const float angle_radians)
{
	if (mode == Axis::AxisAngle) {}

	const float angle_a = 0.5f * angle_radians;
	float cos_a;
	float sin_a;

	Trig::cossin(cos_a, sin_a, angle_a);

	Vec3 qV = vAxis.getNorm();

	qV *= sin_a;

	Vec4 Q;
	Q[x] = qV[x];
	Q[y] = qV[y];
	Q[z] = qV[z];
	Q[w] = cos_a;

	// this function has been transposed
	float x2, y2, z2;
	float xx, xy, xz;
	float yy, yz, zz;
	float wx, wy, wz;

	// ADD test to make sure that quat is normalized

	x2 = Q[x] + Q[x];
	y2 = Q[y] + Q[y];
	z2 = Q[z] + Q[z];

	xx = Q[x] * x2;
	xy = Q[x] * y2;
	xz = Q[x] * z2;

	yy = Q[y] * y2;
	yz = Q[y] * z2;
	zz = Q[z] * z2;

	wx = Q[w] * x2;
	wy = Q[w] * y2;
	wz = Q[w] * z2;

	this->_m0 = 1.0f - (yy + zz);
	this->_m1 = xy + wz;
	this->_m2 = xz - wy;
	this->_m3 = 0.0f;

	this->_m4 = xy - wz;
	this->_m5 = 1.0f - (xx + zz);
	this->_m6 = yz + wx;
	this->_m7 = 0.0f;

	this->_m8 = xz + wy;
	this->_m9 = yz - wx;
	this->_m10 = 1.0f - (xx + yy);
	this->_m11 = 0.0f;

	this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

	this->privSetRotHint();
}
void Rot::set(const Orient type, const Vec3& dof, const Vec3& up)
{
	Vec3 zAxis = dof;
	zAxis.norm();

	Vec3 xAxis = up.cross(zAxis);
	xAxis.norm();

	Vec3 yAxis = (zAxis.cross(xAxis));
	yAxis.norm();

	if (type == Orient::WorldToLocal) {
		_m0 = xAxis.x(); _m1 = yAxis.x(); _m2 = zAxis.x(); _m3 = 0.0f;
		_m4 = xAxis.y(); _m5 = yAxis.y(); _m6 = zAxis.y(); _m7 = 0.0f;
		_m8 = xAxis.z(); _m9 = yAxis.z(); _m10 = zAxis.z(); _m11 = 0.0f;
	}
	else {
		_m0 = xAxis.x(); _m1 = xAxis.y(); _m2 = xAxis.z(); _m3 = 0.0f;
		_m4 = yAxis.x(); _m5 = yAxis.y(); _m6 = yAxis.z(); _m7 = 0.0f;
		_m8 = zAxis.x(); _m9 = zAxis.y(); _m10 = zAxis.z(); _m11 = 0.0f;
	}

	_m12 = 0.0f; _m13 = 0.0f; _m14 = 0.0f; _m15 = 1.0f;

	this->privSetRotHint();
}
void Rot::set(const Quat& qIn)
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

Mat4 Rot::operator*(const Mat4& A) const
{
	// Store A's inverse hint.
	Hint AHint = A.privGetHint();
	Mat4 m;
	m._m0 = (this->_m0 * A._m0) + (this->_m1 * A._m4) + (this->_m2 * A._m8) + 
		(this->_m3 * A._m12);
	m._m1 = (this->_m0 * A._m1) + (this->_m1 * A._m5) + (this->_m2 * A._m9) + 
		(this->_m3 * A._m13);
	m._m2 = (this->_m0 * A._m2) + (this->_m1 * A._m6) + (this->_m2 * A._m10) + 
		(this->_m3 * A._m14);
	m._m3 = (this->_m0 * A._m3) + (this->_m1 * A._m7) + (this->_m2 * A._m11) + 
		(this->_m3 * A._m15);
	m._m4 = (this->_m4 * A._m0) + (this->_m5 * A._m4) + (this->_m6 * A._m8) + 
		(this->_m7 * A._m12);
	m._m5 = (this->_m4 * A._m1) + (this->_m5 * A._m5) + (this->_m6 * A._m9) + 
		(this->_m7 * A._m13);
	m._m6 = (this->_m4 * A._m2) + (this->_m5 * A._m6) + (this->_m6 * A._m10) + 
		(this->_m7 * A._m14);
	m._m7 = (this->_m4 * A._m3) + (this->_m5 * A._m7) + (this->_m6 * A._m11) + 
		(this->_m7 * A._m15);
	m._m8 = (this->_m8 * A._m0) + (this->_m9 * A._m4) + (this->_m10 * A._m8) + 
		(this->_m11 * A._m12);
	m._m9 = (this->_m8 * A._m1) + (this->_m9 * A._m5) + (this->_m10 * A._m9) + 
		(this->_m11 * A._m13);
	m._m10 = (this->_m8 * A._m2) + (this->_m9 * A._m6) + (this->_m10 * A._m10) + 
		(this->_m11 * A._m14);
	m._m11 = (this->_m8 * A._m3) + (this->_m9 * A._m7) + (this->_m10 * A._m11) + 
		(this->_m11 * A._m15);
	m._m12 = (this->_m12 * A._m0) + (this->_m13 * A._m4) + (this->_m14 * A._m8) + 
		(this->_m15 * A._m12);
	m._m13 = (this->_m12 * A._m1) + (this->_m13 * A._m5) + (this->_m14 * A._m9) + 
		(this->_m15 * A._m13);
	m._m14 = (this->_m12 * A._m2) + (this->_m13 * A._m6) + (this->_m14 * A._m10) + 
		(this->_m15 * A._m14);
	m._m15 = (this->_m12 * A._m3) + (this->_m13 * A._m7) + (this->_m14 * A._m11) + 
		(this->_m15 * A._m15);
	// Apply A's inverse hint combined with this matrix's hint. 
	m.privSetNewHint(AHint, this->privGetHint());
	return m;
}
Mat4 Rot::operator*(const Scale& A) const
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
	m.privSetRotHint();
	m.privSetScaleHint();
	return m;
}
Rot Rot::operator*(const Rot& A) const
{
	Rot m;
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
	m.privSetRotHint();
	return m;
}
Rot& Rot::operator*=(const Rot& A)
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
Mat4 Rot::operator*(const Trans& A) const
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
	m.privSetRotHint();
	return m;
}

Rot Rot::operator*(const Quat& q) const
{
	return *this * Rot(q);
}
Rot& Rot::operator*=(const Quat& q)
{
	return *this *= Rot(q);
}
