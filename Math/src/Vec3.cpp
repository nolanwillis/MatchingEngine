#include "Vec3.h"
#include "Mat3.h"
#include "Trig.h"
#include "Vec2.h"
#include "Vec4.h"

#include <cstdio>

Vec3::Vec3()
	:
	_vx(0.0f),
	_vy(0.0f),
	_vz(0.0f)
{}
Vec3::Vec3(const float x, const float y, const float z)
{
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
}
Vec3::Vec3(const Vec2& rhs)
{	
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = 0.0f;
}
Vec3::Vec3(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
}
Vec3::Vec3(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
}
Vec3& Vec3::operator=(const Vec2& rhs)
{	
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = 0.0f;
	return *this;
}
Vec3& Vec3::operator=(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	return *this;
}
Vec3& Vec3::operator=(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	return *this;
}

float& Vec3::operator[] (const enum x_enum)
{
	return this->_vx;
}
float& Vec3::operator[] (const enum y_enum)
{
	return this->_vy;
}
float& Vec3::operator[] (const enum z_enum)
{
	return this->_vz;
}
float Vec3::operator[] (const enum x_enum) const
{
	return this->_vx;
}
float Vec3::operator[] (const enum y_enum) const
{
	return this->_vy;
}
float Vec3::operator[] (const enum z_enum) const
{
	return this->_vz;
}
float Vec3::x() const
{
	return this->_vx;
}
float Vec3::y() const
{
	return this->_vy;
}
float Vec3::z() const
{
	return this->_vz;
}
void Vec3::x(const float x)
{
	this->_vx = x;
}
void Vec3::y(const float y)
{
	this->_vy = y;
}
void Vec3::z(const float z)
{
	this->_vz = z;
}
void Vec3::set(const float x, const float y, const float z)
{
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
}
void Vec3::set(const Vec2& inVec2)
{
	this->_vx = inVec2._vx;
	this->_vy = inVec2._vy;
}
void Vec3::set(const Vec3& inVec3)
{
	this->_vx = inVec3._vx;
	this->_vy = inVec3._vy;
	this->_vz = inVec3._vz;
}
void Vec3::set(const Vec4& inVec4)
{
	this->_vx = inVec4._vx;
	this->_vy = inVec4._vy;
	this->_vz = inVec4._vz;
}

Vec3 Vec3::operator+() const
{
	float x = this->_vx < 0 ? -1.0f * this->_vx : this->_vx;
	float y = this->_vy < 0 ? -1.0f * this->_vy : this->_vy;
	float z = this->_vz < 0 ? -1.0f * this->_vz : this->_vz;
	return Vec3(x, y, z);
}
Vec3 Vec3::operator+(const Vec3& inVec3) const
{
	return Vec3(this->_vx + inVec3._vx, this->_vy + inVec3._vy, this->_vz + inVec3._vz);
}
Vec3& Vec3::operator+=(const Vec3& inVec3)
{
	this->_vx += inVec3._vx;
	this->_vy += inVec3._vy;
	this->_vz += inVec3._vz;
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-1.0f * this->_vx, -1.0f * this->_vy, -1.0f * this->_vz);
}
Vec3 Vec3::operator-(const Vec3& inVec3) const
{
	return Vec3(this->_vx - inVec3._vx, this->_vy - inVec3._vy, this->_vz - inVec3._vz);
}
Vec3& Vec3::operator-=(const Vec3& inVec3)
{
	this->_vx -= inVec3._vx;
	this->_vy -= inVec3._vy;
	this->_vz -= inVec3._vz;
	return *this;
}

Vec3 Vec3::operator*(const float scale) const
{
	return Vec3(_vx * scale, _vy * scale, _vz * scale);
}
Vec3& Vec3::operator*=(const float scale)
{
	this->_vx *= scale;
	this->_vy *= scale;
	this->_vz *= scale;
	return *this;
}
Vec3 operator*(const float scale, const Vec3& inVec3)
{
	return Vec3(inVec3._vx * scale, inVec3._vy * scale, inVec3._vz * scale);
}
Vec3 Vec3::operator*(const Mat3& m) const
{
	return Vec3
	(
		(_vx * m._m0) + (_vy * m._m4) + (_vz * m._m8),
		(_vx * m._m1) + (_vy * m._m5) + (_vz * m._m9),
		(_vx * m._m2) + (_vy * m._m6) + (_vz * m._m10)
	);
}
Vec3& Vec3::operator*=(const Mat3& m)
{
	float x = (_vx * m._m0) + (_vy * m._m4) + (_vz * m._m8);
	float y = (_vx * m._m1) + (_vy * m._m5) + (_vz * m._m9);
	float z = (_vx * m._m2) + (_vy * m._m6) + (_vz * m._m10);
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
	return *this;
}
Vec3 Vec3::operator*(const Quat& q) const
{
	return *this * Mat3(q);
}
Vec3& Vec3::operator*=(const Quat& q)
{
	return *this *= Mat3(q);
}

Vec3& Vec3::norm()
{
	float mag = Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz));
	this->_vx /= mag;
	this->_vy /= mag;
	this->_vz /= mag;
	return *this;
}
Vec3 Vec3::getNorm() const
{
	float mag = Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz));
	return Vec3(this->_vx / mag, this->_vy / mag, this->_vz / mag);
}
float Vec3::dot(const Vec3& vIn) const
{
	return ((this->_vx * vIn._vx) + (this->_vy * vIn._vy) + (this->_vz * vIn._vz));
}
Vec3 Vec3::cross(const Vec3& vIn) const
{
	float x = (_vy * vIn._vz) - (_vz * vIn._vy);
	float y = (_vx * vIn._vz) - (_vz * vIn._vx);
	float z = (_vx * vIn._vy) - (_vy * vIn._vx);
	return Vec3(x, -1 * y, z);
}
Vec3Proxy Vec3::len() const
{
	return Vec3Proxy(_vx, _vy, _vz);
}
float Vec3::getAngle(const Vec3& vIn) const
{
	float dot = this->dot(vIn);
	float mag1 = this->len();
	float mag2 = vIn.len();
	return Trig::acos(dot / (mag1 * mag2));
}

bool Vec3::isEqual(const Vec3& v, const float epsilon) const
{
	return (_vx <= v._vx + epsilon && _vx >= v._vx - epsilon &&
		_vy <= v._vy + epsilon && _vy >= v._vy - epsilon &&
		_vz <= v._vz + epsilon && _vz >= v._vz - epsilon);
}
bool Vec3::isZero(const float epsilon) const
{
	return (_vx <= epsilon && _vx >= 0 - epsilon &&
		_vy <= epsilon && _vy >= 0 - epsilon &&
		_vz <= epsilon && _vz >= 0 - epsilon);
}

void Vec3::Print(const char* pName) const
{
	std::printf("%s: (%f, %f, %f)\n", pName, _vx, _vy, _vz);
}
