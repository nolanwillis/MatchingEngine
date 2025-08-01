#include "Vec4.h"
#include "Mat4.h"
#include "Trig.h"
#include "Vec2.h"
#include "Vec3.h"

#include <cstdio>

Vec4::Vec4()
	:
	_vx(0.0f),
	_vy(0.0f),
	_vz(0.0f),
	_vw(0.0f)
{}
Vec4::Vec4(const float x, const float y, const float z, const float w = 1.0f)
{
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
	this->_vw = w;
}
Vec4::Vec4(const Vec3& inVec3, const float w)
{
	this->_vx = inVec3._vx;
	this->_vy = inVec3._vy;
	this->_vz = inVec3._vz;
	this->_vw = w;
}
Vec4::Vec4(const Vec2& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = 0.0f;
	this->_vw = 0.0f;
}
Vec4::Vec4(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	this->_vw = 0.0f;
}
Vec4::Vec4(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	this->_vw = rhs._vw;
}
Vec4& Vec4::operator=(const Vec2& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = 0.0f;
	this->_vw = 0.0f;
	return *this;
}
Vec4& Vec4::operator=(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	this->_vw = 0.0f;
	return *this;
}
Vec4& Vec4::operator=(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	this->_vz = rhs._vz;
	this->_vw = rhs._vw;
	return *this;
}

float& Vec4::operator[] (const enum x_enum)
{
	return this->_vx;
}
float& Vec4::operator[] (const enum y_enum)
{
	return this->_vy;
}
float& Vec4::operator[] (const enum z_enum)
{
	return this->_vz;
}
float& Vec4::operator[] (const enum w_enum)
{
	return this->_vw;
}
float Vec4::operator[] (const enum x_enum) const
{
	return this->_vx;
}
float Vec4::operator[] (const enum y_enum) const
{
	return this->_vy;
}
float Vec4::operator[] (const enum z_enum) const
{
	return this->_vz;
}
float Vec4::operator[](const w_enum) const
{
	return this->_vw;
}
float Vec4::x() const
{
	return this->_vx;
}
float Vec4::y() const
{
	return this->_vy;
}
float Vec4::z() const
{
	return this->_vz;
}
float Vec4::w() const
{
	return this->_vw;
}
void Vec4::x(const float x)
{
	this->_vx = x;
}
void Vec4::y(const float y)
{
	this->_vy = y;
}
void Vec4::z(const float z)
{
	this->_vz = z;
}
void Vec4::w(const float w)
{
	this->_vw = w;
}
void Vec4::set(const float x, const float y, const float z, const float w)
{
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
	this->_vw = w;
}
void Vec4::set(const Vec3& inVec3, const float w)
{
	this->_vx = inVec3._vx;
	this->_vy = inVec3._vy;
	this->_vz = inVec3._vz;
	this->_vw = w;
}
void Vec4::set(const Vec2& inVec2)
{
	this->_vx = inVec2._vx;
	this->_vy = inVec2._vy;
	this->_vz = 0.0f;
	this->_vw = 0.0f;
}
void Vec4::set(const Vec3& inVec3)
{
	this->_vx = inVec3._vx;
	this->_vy = inVec3._vy;
	this->_vz = inVec3._vz;
	this->_vw = 0.0f;
}
void Vec4::set(const Vec4& inVec4)
{
	this->_vx = inVec4._vx;
	this->_vy = inVec4._vy;
	this->_vz = inVec4._vz;
	this->_vw = inVec4._vw;
}

Vec4 Vec4::operator+() const
{
	float x = this->_vx < 0 ? -1.0f * this->_vx : this->_vx;
	float y = this->_vy < 0 ? -1.0f * this->_vy : this->_vy;
	float z = this->_vz < 0 ? -1.0f * this->_vz : this->_vz;
	float w = this->_vw < 0 ? -1.0f * this->_vw : this->_vw;
	return Vec4(x, y, z, w);
}
Vec4 Vec4::operator+(const Vec4& inV) const
{
	return Vec4(this->_vx + inV._vx, this->_vy + inV._vy, this->_vz + inV._vz, 
		this->_vw + inV._vw);
}
Vec4& Vec4::operator+=(const Vec4& inV)
{
	this->_vx += inV._vx;
	this->_vy += inV._vy;
	this->_vz += inV._vz;
	this->_vw += inV._vw;
	return *this;
}

Vec4 Vec4::operator-(void) const
{
	return Vec4(-1.0f * this->_vx, -1.0f * this->_vy, -1.0f * this->_vz, -1.0f * this->_vw);
}
Vec4 Vec4::operator-(const Vec4& inVec4) const
{
	return Vec4(this->_vx - inVec4._vx, this->_vy - inVec4._vy, this->_vz - inVec4._vz, 
		this->_vw - inVec4._vw);
}
Vec4& Vec4::operator-=(const Vec4& inVec4)
{
	this->_vx -= inVec4._vx;
	this->_vy -= inVec4._vy;
	this->_vz -= inVec4._vz;
	this->_vw -= inVec4._vw;
	return *this;
}

Vec4 Vec4::operator*(const float scale) const
{
	return Vec4(this->_vx * scale, this->_vy * scale, this->_vz * scale, this->_vw * scale);
}
Vec4& Vec4::operator*=(const float scale)
{
	this->_vx *= scale;
	this->_vy *= scale;
	this->_vz *= scale;
	this->_vw *= scale;
	return *this;
}
Vec4 operator*(const float scale, const Vec4& inVec4)
{
	return Vec4(inVec4._vx * scale, inVec4._vy * scale, inVec4._vz * scale, 
		inVec4._vw * scale);
}
Vec4 Vec4::operator*(const Mat4& m) const
{
	return Vec4(
		(_vx * m._m0) + (_vy * m._m4) + (_vz * m._m8) + (_vw * m._m12),
		(_vx * m._m1) + (_vy * m._m5) + (_vz * m._m9) + (_vw * m._m13),
		(_vx * m._m2) + (_vy * m._m6) + (_vz * m._m10) + (_vw * m._m14),
		(_vx * m._m3) + (_vy * m._m7) + (_vz * m._m11) + (_vw * m._m15)
	);
}
Vec4& Vec4::operator*=(const Mat4& m)
{
	float x = (_vx * m._m0) + (_vy * m._m4) + (_vz * m._m8) + (_vw * m._m12);
	float y = (_vx * m._m1) + (_vy * m._m5) + (_vz * m._m9) + (_vw * m._m13);
	float z = (_vx * m._m2) + (_vy * m._m6) + (_vz * m._m10) + (_vw * m._m14);
	float w = (_vx * m._m3) + (_vy * m._m7) + (_vz * m._m11) + (_vw * m._m15);
	this->_vx = x;
	this->_vy = y;
	this->_vz = z;
	this->_vw = w;
	return *this;
}

Vec4& Vec4::norm()
{
	float mag = Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz) + (_vw * _vw));
	this->_vx /= mag;
	this->_vy /= mag;
	this->_vz /= mag;
	this->_vw /= mag;
	return *this;
}
Vec4 Vec4::getNorm() const
{
	float mag = Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz) + (_vw * _vw));
	return Vec4(this->_vx / mag, this->_vy / mag, this->_vz / mag, this->_vw / mag);
}
float Vec4::dot(const Vec4& vIn) const
{
	return ((this->_vx * vIn._vx) + (this->_vy * vIn._vy)
		+ (this->_vz * vIn._vz) + (this->_vw * vIn._vw));
}
Vec4Proxy Vec4::len() const
{
	return Vec4Proxy(_vx, _vy, _vz, _vw);
}

bool Vec4::isEqual(const Vec4& v, const float epsilon) const
{
	return (_vx <= v._vx + epsilon && _vx >= v._vx - epsilon &&
		_vy <= v._vy + epsilon && _vy >= v._vy - epsilon &&
		_vz <= v._vz + epsilon && _vz >= v._vz - epsilon &&
		_vw <= v._vw + epsilon && _vw >= v._vw - epsilon);
}
bool Vec4::isZero(const float epsilon) const
{
	return (_vx <= epsilon && _vx >= -epsilon &&
		_vy <= epsilon && _vy >= -epsilon &&
		_vz <= epsilon && _vz >= -epsilon &&
		_vw <= epsilon && _vw >= -epsilon);
}

void Vec4::Print(const char* pName) const
{
	printf("%s: (%f, %f, %f, %f)", pName, _vx, _vy, _vz, _vw);
}
