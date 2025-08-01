#include "Quat.h"
#include "Rot.h"
#include "Trig.h"

Quat::Quat()
	: _qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
{}
Quat::Quat(const enum Identity_enum)
	: _qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
{}
Quat::Quat(const Quat& qIn)
{
	this->_qx = qIn._qx;
	this->_qz = qIn._qz;
	this->_qy = qIn._qy;
	this->_qw = qIn._qw;
}
Quat::Quat(const Vec3& vec, const float real)
{
	this->_qx = vec.x();
	this->_qy = vec.y();
	this->_qz = vec.z();
	this->_qw = real;
}
Quat::Quat(const float vx, const float vy, const float vz, const float real)
{
	this->_qx = vx;
	this->_qy = vy;
	this->_qz = vz;
	this->_qw = real;
}
Quat::Quat(const Rot& rot)
{
	float tr = rot.m0() + rot.m5() + rot.m10();
	float S;
	if (tr > 0.0f)
	{
		S = 2 * Trig::sqrt(tr + 1.0f);
		this->_qw = 0.25f * S;
		this->_qx = -(rot.m9() - rot.m6()) / S;
		this->_qy = -(rot.m2() - rot.m8()) / S;
		this->_qz = -(rot.m4() - rot.m1()) / S;
	}
	else if ((rot.m0() > rot.m5()) && (rot.m0() > rot.m10()))
	{
		S = 2 * Trig::sqrt(1.0f + rot.m0() - rot.m5() - rot.m10());
		this->_qw = -(rot.m9() - rot.m6()) / S;
		this->_qx = 0.25f * S;
		this->_qy = (rot.m1() + rot.m4()) / S;
		this->_qz = (rot.m2() + rot.m8()) / S;
	}
	else if (rot.m5() > rot.m10())
	{
		S = 2 * Trig::sqrt(1.0f + rot.m5() - rot.m0() - rot.m10());
		this->_qw = -(rot.m2() - rot.m8()) / S;
		this->_qx = (rot.m1() + rot.m4()) / S;
		this->_qy = 0.25f * S;
		this->_qz = (rot.m6() + rot.m9()) / S;
	}
	else
	{
		S = 2 * Trig::sqrt(1.0f + rot.m10() - rot.m0() - rot.m5());
		this->_qw = -(rot.m4() - rot.m1()) / S;
		this->_qx = (rot.m2() + rot.m8()) / S;
		this->_qy = (rot.m6() + rot.m9()) / S;
		this->_qz = 0.25f * S;
	}
}
Quat::Quat(const Rot1 type, const float angle_radians)
{
	switch (type)
	{
	case Rot1::X:
		this->_qx = Trig::sin(angle_radians / 2.0f);
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = Trig::cos(angle_radians / 2.0f);
		break;
	case Rot1::Y:
		this->_qx = 0.0f;
		this->_qy = Trig::sin(angle_radians / 2.0f);
		this->_qz = 0.0f;
		this->_qw = Trig::cos(angle_radians / 2.0f);
		break;
	case Rot1::Z:
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = Trig::sin(angle_radians / 2.0f);
		this->_qw = Trig::cos(angle_radians / 2.0f);
		break;
	default:
		break;
	}
}
Quat::Quat(const Rot3 type, const float angle_x, const float angle_y, const float angle_z)
{
	switch (type)
	{
	case Rot3::XYZ:
		*this = Quat(Rot1::X, angle_x) * Quat(Rot1::Y, angle_y) * Quat(Rot1::Z, angle_z);
		break;
	case Rot3::XZY:	
		*this = Quat(Rot1::X, angle_x) * Quat(Rot1::Z, angle_z) * Quat(Rot1::Y, angle_y);
		break;
	case Rot3::YXZ:	
		*this = Quat(Rot1::Y, angle_y) * Quat(Rot1::X, angle_x) * Quat(Rot1::Z, angle_z);
		break;
	case Rot3::YZX:
		*this = Quat(Rot1::Y, angle_y) * Quat(Rot1::Z, angle_z) * Quat(Rot1::X, angle_x);
		break;
	case Rot3::ZXY:
		*this = Quat(Rot1::Z, angle_z) * Quat(Rot1::X, angle_x) * Quat(Rot1::Y, angle_y);
		break;
	case Rot3::ZYX:
		*this = Quat(Rot1::Z, angle_z) * Quat(Rot1::Y, angle_y) * Quat(Rot1::X, angle_x);
		break;
	default:
		break;
	}
}
Quat::Quat(const Axis type, const Vec3& vAxis, const float angle_radians)
{
	if (type == Axis::AxisAngle)
	{
		this->_qV3 = vAxis.getNorm() * Trig::sin(angle_radians / 2.0f);
		this->_qw = Trig::cos(angle_radians / 2.0f);
	}
	else
	{
		this->_qV3 = vAxis * Trig::sin(angle_radians / 2.0f);
		this->_qw = Trig::cos(angle_radians / 2.0f);
	}
}
Quat::Quat(const Orient orient, const Vec3& dof, const Vec3& up)
{
	// Find forward, up, and right vector.
	Vec3 forwardVector = dof.getNorm();
	Vec3 upVector = up.getNorm();
	Vec3 rightVector = upVector.cross(forwardVector).getNorm();
	upVector = forwardVector.cross(rightVector);
	// Create rotation matrix using the vectors.
	Rot rotMatrix;
	rotMatrix.m0(rightVector.x());
	rotMatrix.m1(rightVector.y());
	rotMatrix.m2(rightVector.z());
	rotMatrix.m4(upVector.x());
	rotMatrix.m5(upVector.y());
	rotMatrix.m6(upVector.z());
	rotMatrix.m8(forwardVector.x());
	rotMatrix.m9(forwardVector.y());
	rotMatrix.m10(forwardVector.z());
	// If this quaternion is performing a world to local transformation, use 
	// the inverse of the computed rotation matrix.
	if (orient == Orient::WorldToLocal)
	{
		rotMatrix.inv();
	}
	// Rotation matrix will be converted into a quaternion.
	*this = rotMatrix;
}

Quat& Quat::operator=(const Quat& q)
{
	this->_mq = q._mq;
	return *this;
}
Quat& Quat::operator=(const Rot& rot)
{
	float tr = rot.m0() + rot.m5() + rot.m10();
	float S;
	if (tr > 0.0f)
	{
		S = 2 * Trig::sqrt(tr + 1.0f);
		this->_qw = 0.25f * S;
		this->_qx = -(rot.m9() - rot.m6()) / S;
		this->_qy = -(rot.m2() - rot.m8()) / S;
		this->_qz = -(rot.m4() - rot.m1()) / S;
	}
	else if ((rot.m0() > rot.m5()) && (rot.m0() > rot.m10()))
	{
		S = 2 * Trig::sqrt(1.0f + rot.m0() - rot.m5() - rot.m10());
		this->_qw = -(rot.m9() - rot.m6()) / S;
		this->_qx = 0.25f * S;
		this->_qy = (rot.m1() + rot.m4()) / S;
		this->_qz = (rot.m2() + rot.m8()) / S;
	}
	else if (rot.m5() > rot.m10())
	{
		S = 2 * Trig::sqrt(1.0f + rot.m5() - rot.m0() - rot.m10());
		this->_qw = -(rot.m2() - rot.m8()) / S;
		this->_qx = (rot.m1() + rot.m4()) / S;
		this->_qy = 0.25f * S;
		this->_qz = (rot.m6() + rot.m9()) / S;
	}
	else
	{
		S = 2 * Trig::sqrt(1.0f + rot.m10() - rot.m0() - rot.m5());
		this->_qw = -(rot.m4() - rot.m1()) / S;
		this->_qx = (rot.m2() + rot.m8()) / S;
		this->_qy = (rot.m6() + rot.m9()) / S;
		this->_qz = 0.25f * S;
	}
	return *this;
}

void Quat::set(const Rot& rot)
{
	float tr = rot.m0() + rot.m5() + rot.m10();
	float S;
	if (tr > 0.0f)
	{
		S = 2 * Trig::sqrt(tr + 1.0f);
		this->_qw = 0.25f * S;
		this->_qx = -(rot.m9() - rot.m6()) / S;
		this->_qy = -(rot.m2() - rot.m8()) / S;
		this->_qz = -(rot.m4() - rot.m1()) / S;
	}
	else if ((rot.m0() > rot.m5()) && (rot.m0() > rot.m10()))
	{
		S = 2 * Trig::sqrt(1.0f + rot.m0() - rot.m5() - rot.m10());
		this->_qw = -(rot.m9() - rot.m6()) / S;
		this->_qx = 0.25f * S;
		this->_qy = (rot.m1() + rot.m4()) / S;
		this->_qz = (rot.m2() + rot.m8()) / S;
	}
	else if (rot.m5() > rot.m10())
	{
		S = 2 * Trig::sqrt(1.0f + rot.m5() - rot.m0() - rot.m10());
		this->_qw = -(rot.m2() - rot.m8()) / S;
		this->_qx = (rot.m1() + rot.m4()) / S;
		this->_qy = 0.25f * S;
		this->_qz = (rot.m6() + rot.m9()) / S;
	}
	else
	{
		S = 2 * Trig::sqrt(1.0f + rot.m10() - rot.m0() - rot.m5());
		this->_qw = -(rot.m4() - rot.m1()) / S;
		this->_qx = (rot.m2() + rot.m8()) / S;
		this->_qy = (rot.m6() + rot.m9()) / S;
		this->_qz = 0.25f * S;
	}
}
void Quat::set(const Rot1 type, const float angle)
{
	switch (type)
	{
	case Rot1::X:
		this->_qx = Trig::sin(angle / 2.0f);
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = Trig::cos(angle / 2.0f);
		break;
	case Rot1::Y:
		this->_qx = 0.0f;
		this->_qy = Trig::sin(angle / 2.0f);
		this->_qz = 0.0f;
		this->_qw = Trig::cos(angle / 2.0f);
		break;
	case Rot1::Z:
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = Trig::sin(angle / 2.0f);
		this->_qw = Trig::cos(angle / 2.0f);
		break;
	default:
		break;
	}
}
void Quat::set(const Rot3 type, const float angle_x, const float angle_y, 
	const float angle_z)
{
	switch (type)
	{
	case Rot3::XYZ:
		*this = Quat(Rot1::X, angle_x) * Quat(Rot1::Y, angle_y) * Quat(Rot1::Z, angle_z);
		break;
	case Rot3::XZY:
		*this = Quat(Rot1::X, angle_x) * Quat(Rot1::Z, angle_z) * Quat(Rot1::Y, angle_y);
		break;
	case Rot3::YXZ:
		*this = Quat(Rot1::Y, angle_y) * Quat(Rot1::X, angle_x) * Quat(Rot1::Z, angle_z);
		break;
	case Rot3::YZX:
		*this = Quat(Rot1::Y, angle_y) * Quat(Rot1::Z, angle_z) * Quat(Rot1::X, angle_x);
		break;
	case Rot3::ZXY:
		*this = Quat(Rot1::Z, angle_z) * Quat(Rot1::X, angle_x) * Quat(Rot1::Y, angle_y);
		break;
	case Rot3::ZYX:
		*this = Quat(Rot1::Z, angle_z) * Quat(Rot1::Y, angle_y) * Quat(Rot1::X, angle_x);
		break;
	default:
		break;
	}
}
void Quat::set(const Axis type, const Vec3& vAxis, const float angle_radians)
{
	if (type == Axis::AxisAngle)
	{
		this->_qV3 = vAxis.getNorm() * Trig::sin(angle_radians / 2.0f);
		this->_qw = Trig::cos(angle_radians / 2.0f);
	}
	else
	{
		this->_qV3 = vAxis * Trig::sin(angle_radians / 2.0f);
		this->_qw = Trig::cos(angle_radians / 2.0f);
	}
}
void Quat::set(const Orient orient, const Vec3& dof, const Vec3& up)
{
	// Find forward, up, and right vector.
	Vec3 forwardVector = dof.getNorm();
	Vec3 upVector = up.getNorm();
	Vec3 rightVector = upVector.cross(forwardVector).getNorm();
	upVector = forwardVector.cross(rightVector);
	// Create rotation matrix using the vectors.
	Rot rotMatrix;
	rotMatrix.m0(rightVector.x());
	rotMatrix.m1(rightVector.y());
	rotMatrix.m2(rightVector.z());
	rotMatrix.m4(upVector.x());
	rotMatrix.m5(upVector.y());
	rotMatrix.m6(upVector.z());
	rotMatrix.m8(forwardVector.x());
	rotMatrix.m9(forwardVector.y());
	rotMatrix.m10(forwardVector.z());
	// If this quaternion is performing a world to local transformation, use 
	// the inverse of the computed rotation matrix.
	if (orient == Orient::WorldToLocal)
	{
		rotMatrix.inv();
	}
	// Rotation matrix will be converted into a quaternion.
	*this = rotMatrix;
}
void Quat::set(const enum Identity_enum)
{
	this->_qx = 0.0f;
	this->_qy = 0.0f;
	this->_qz = 0.0f;
	this->_qw = 1.0f;
}
void Quat::set(const float vx, const float vy, const float vz, const float real)
{
	this->_qx = vx;
	this->_qy = vy;
	this->_qz = vz;
	this->_qw = real;
}
void Quat::set(const Vec3& vect, const float real)
{
	this->_qx = vect.x();
	this->_qy = vect.y();
	this->_qz = vect.z();
	this->_qw = real;
}
void Quat::setVec3(const Vec3& vect)
{
	this->_qx = vect.x();
	this->_qy = vect.y();
	this->_qz = vect.z();
}

void Quat::qx(const float vx)
{
	this->_qx = vx;
}
void Quat::qy(const float vy)
{
	this->_qy = vy;
}
void Quat::qz(const float vz)
{
	this->_qz = vz;
}
void Quat::real(const float real)
{
	this->_qw = real;
}

float& Quat::operator[](const x_enum)
{
	return this->_qx;
}
float& Quat::operator[](const y_enum)
{
	return this->_qy;
}
float& Quat::operator[](const z_enum)
{
	return this->_qz;
}
float& Quat::operator[](const w_enum)
{
	return this->_qw;
}
float Quat::operator[](const x_enum) const
{
	return this->_qx;
}
float Quat::operator[](const y_enum) const
{
	return this->_qy;
}
float Quat::operator[](const z_enum) const
{
	return this->_qz;
}
float Quat::operator[](const w_enum) const
{
	return this->_qw;
}

float Quat::qx() const
{
	return this->_qx;
}
float Quat::qy() const
{
	return this->_qy;
}
float Quat::qz() const
{
	return this->_qz;
}
float Quat::real() const
{
	return this->_qw;
}

float Quat::getAngle() const
{
	return 2 * Trig::acos(this->_qw);
}
void Quat::getVec3(Vec3& vOut) const
{
	vOut = this->_qV3;
}
void Quat::getAxis(Vec3& vOut) const
{
	float sinThetaOver2 = Trig::sqrt(1.0f - this->_qw * this->_qw);
	vOut.x(this->_qx / sinThetaOver2);
	vOut.y(this->_qy / sinThetaOver2);
	vOut.z(this->_qz / sinThetaOver2);
}

float Quat::dot(const Quat& qin) const
{
	return (this->_qx * qin._qx) + (this->_qy * qin._qy) + (this->_qz * qin._qz) +
		(this->_qw * qin._qw);
}
float Quat::mag() const
{
	return Trig::sqrt((this->_qx * this->_qx) + (this->_qy * this->_qy) + 
		(this->_qz * this->_qz) + (this->_qw * this->_qw));
}
float Quat::magSquared() const
{
	return (this->_qx * this->_qx) + (this->_qy * this->_qy) + (this->_qz * this->_qz) + 
		(this->_qw * this->_qw);
}
float Quat::invMag() const
{
	return 1.0f / Trig::sqrt((this->_qx * this->_qx) + (this->_qy * this->_qy) + 
		(this->_qz * this->_qz) + (this->_qw * this->_qw));
}
Quat& Quat::conj()
{
	this->_qx = -this->_qx;
	this->_qy = -this->_qy;
	this->_qz = -this->_qz;
	return *this;
}
Quat Quat::getConj() const
{
	return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
}
Quat& Quat::inv()
{
	return this->conj() /= this->mag();
}
Quat Quat::getInv() const
{
	return Quat(this->getConj() / this->mag());
}
Quat& Quat::norm()
{
	return *this /= this->mag();
}
Quat Quat::getNorm() const
{
	return Quat(*this / this->mag());
}

void Quat::Lqvqc(const Vec3& vIn, Vec3& vOut) const
{
	vOut = (2 * this->_qw * (vIn.cross(this->_qV3)) +
		(((this->_qw * this->_qw) - this->_qV3.dot(this->_qV3)) * vIn) +
		(2 * (this->_qV3.dot(vIn) * this->_qV3)));
}
void Quat::Lqcvq(const Vec3& vIn, Vec3& vOut) const
{
	vOut = (2 * this->_qw * (this->_qV3.cross(vIn)) +
		(((this->_qw * this->_qw) - this->_qV3.dot(this->_qV3)) * vIn) +
		(2 * (this->_qV3.dot(vIn) * this->_qV3)));
}

bool Quat::isEqual(const Quat& qin, const float epsilon) const
{
	return (this->_qx <= qin._qx + epsilon && this->_qx >= qin._qx - epsilon &&
		this->_qy <= qin._qy + epsilon && this->_qy >= qin._qy - epsilon &&
		this->_qz <= qin._qz + epsilon && this->_qz >= qin._qz - epsilon &&
		this->_qw <= qin._qw + epsilon && this->_qw >= qin._qw - epsilon);
}
bool Quat::isEquivalent(const Quat& qin, const float epsilon) const
{
	return isEqual(qin, epsilon) || isNegEqual(qin, epsilon);
}
bool Quat::isNegEqual(const Quat& qin, const float epsilon) const
{
	return (-this->_qx <= qin._qx + epsilon && -this->_qx >= qin._qx - epsilon &&
		-this->_qy <= qin._qy + epsilon && -this->_qy >= qin._qy - epsilon &&
		-this->_qz <= qin._qz + epsilon && -this->_qz >= qin._qz - epsilon &&
		-this->_qw <= qin._qw + epsilon && -this->_qw >= qin._qw - epsilon);
}
bool Quat::isConjugateEqual(const Quat& qin, const float epsilon) const
{
	Quat conj = this->getConj();
	return (conj._qx <= qin._qx + epsilon && conj._qx >= qin._qx - epsilon &&
		conj._qy <= qin._qy + epsilon && conj._qy >= qin._qy - epsilon &&
		conj._qz <= qin._qz + epsilon && conj._qz >= qin._qz - epsilon &&
		conj._qw <= qin._qw + epsilon && conj._qw >= qin._qw - epsilon);
}
bool Quat::isIdentity(const float epsilon) const
{
	return (this->_qx <= 0.0f + epsilon && this->_qx >= 0.0f - epsilon &&
		this->_qy <= 0.0f + epsilon && this->_qy >= 0.0f - epsilon &&
		this->_qz <= 0.0f + epsilon && this->_qz >= 0.0f - epsilon &&
		this->_qw <= 1.0f + epsilon && this->_qw >= 1.0f - epsilon);
}
bool Quat::isNormalized(const float epsilon) const
{
	return (this->magSquared() >= 1.0f - epsilon &&
		this->magSquared() <= 1.0f + epsilon);
}

Quat Quat::operator+() const
{
	return Quat(+this->_qx, +this->_qy, +this->_qz, this->_qw);
}
Quat Quat::operator+(const Quat& q) const
{
	return Quat(this->_qx + q._qx, this->_qy + q._qy, this->_qz + q._qz, 
		this->_qw + q._qw);
}
Quat& Quat::operator+=(const Quat& q)
{
	this->_qx += q._qx;
	this->_qy += q._qy;
	this->_qz += q._qz;
	this->_qw += q._qw;
	return *this;
}
Quat Quat::operator+(const float a) const
{
	return Quat(this->_qx + a, this->_qy + a, this->_qz + a, this->_qw + a);
}
Quat& Quat::operator+=(const float a)
{
	this->_qx += a;
	this->_qy += a;
	this->_qz += a;
	this->_qw += a;
	return *this;
}
Quat operator+(const float a, const Quat& q)
{
	return Quat(a + q._qx, a + q._qy, a + q._qz, a + q._qw);
}

Quat Quat::operator-() const
{
	return Quat(-this->_qx, -this->_qy, -this->_qz, -this->_qw);
}
Quat Quat::operator-(const Quat& q) const
{
	return Quat(this->_qx - q._qx, this->_qy - q._qy, this->_qz - q._qz,
		this->_qw - q._qw);
}
Quat& Quat::operator-=(const Quat& q)
{
	this->_qx -= q._qx;
	this->_qy -= q._qy;
	this->_qz -= q._qz;
	this->_qw -= q._qw;
	return *this;
}
Quat Quat::operator-(const float a) const
{
	return Quat(this->_qx - a, this->_qy - a, this->_qz - a, this->_qw - a);
}
Quat& Quat::operator-=(const float a)
{
	this->_qx -= a;
	this->_qy -= a;
	this->_qz -= a;
	this->_qw -= a;
	return *this;
}
Quat operator-(const float a, const Quat& q)
{
	return Quat(a - q._qx, a - q._qy, a - q._qz, a - q._qw);
}

Quat Quat::operator*(const Quat& q) const
{
	return Quat
	(
		q._qV3.cross(this->_qV3) + (q._qw * this->_qV3) + (this->_qw * q._qV3),
		this->_qw * q._qw - this->_qV3.dot(q._qV3)
	);
}
Quat& Quat::operator*=(const Quat& q)
{
	Vec3 vect = q._qV3.cross(this->_qV3) + (q._qw * this->_qV3) + (this->_qw * q._qV3); 
	float w = this->_qw * q._qw - this->_qV3.dot(q._qV3);
	this->_qV3 = vect;
	this->_qw = w;
	return *this;
}
Quat Quat::operator*(const float a) const
{
	return Quat(this->_qx*a, this->_qy*a, this->_qz*a, this->_qw*a);
}
Quat& Quat::operator*=(const float a)
{
	this->_qx *= a;
	this->_qy *= a;
	this->_qz *= a;
	this->_qw *= a;
	return *this;
}
Mat4 Quat::operator*(const Mat4& m) const
{
	return Rot(*this) * m;
}
Mat4 Quat::operator*(const Scale& m) const
{
	return Rot(*this) * m;
}
Rot Quat::operator*(const Rot& m) const
{
	return Rot(*this) * m;
}
Quat& Quat::operator*=(const Rot& m)
{
	return *this *= Quat(m);
}
Mat4 Quat::operator*(const Trans& m) const
{
	return Rot(*this) * m;
}
Quat operator*(const float a, const Quat& q)
{
	return Quat(a * q._qx, a * q._qy, a * q._qz, a * q._qw);
}

Quat Quat::operator/(const Quat& q) const
{
	return Quat(this->_qx / q._qx, this->_qy / q._qy, this->_qz / q._qz,
		this->_qw / q._qw);
}
Quat& Quat::operator/=(const Quat& q)
{
	this->_qx /= q._qx;
	this->_qy /= q._qy;
	this->_qz /= q._qz;
	this->_qw /= q._qw;
	return *this;
}
Quat Quat::operator/(const float a) const
{
	return Quat(this->_qx / a, this->_qy / a, this->_qz / a, this->_qw / a);
}
Quat& Quat::operator/=(const float a)
{
	this->_qx /= a;
	this->_qy /= a;
	this->_qz /= a;
	this->_qw /= a;
	return *this;
}

Quat operator/(const float a, const Quat& q)
{
	return Quat(a / q._qx, a / q._qy, a / q._qz, a / q._qw);
}
