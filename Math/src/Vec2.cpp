#include "Vec2.h"
#include "Trig.h"
#include "Vec3.h"
#include "Vec4.h"

#include <cstdio>

Vec2::Vec2()
	:
	_vx(0.0f),
	_vy(0.0f)
{}
Vec2::Vec2(const float x, const float y)
{
	this->_vx = x;
	this->_vy = y;
}
Vec2::Vec2(const Vec2& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
}
Vec2::Vec2(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
}
Vec2::Vec2(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
}
Vec2& Vec2::operator=(const Vec2& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	return *this;
}
Vec2& Vec2::operator=(const Vec3& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	return *this;
}
Vec2& Vec2::operator=(const Vec4& rhs)
{
	this->_vx = rhs._vx;
	this->_vy = rhs._vy;
	return *this;
}

float& Vec2::operator[](const x_enum)
{
	return this->_vx;
}
float& Vec2::operator[](const y_enum)
{
	return this->_vy;
}
float Vec2::operator[](const x_enum) const
{
	return this->_vx;
}
float Vec2::operator[](const y_enum) const
{
	return this->_vy;
}
float Vec2::x() const
{
	return this->_vx;
}
float Vec2::y() const
{
	return this->_vy;
}
void Vec2::x(const float x)
{
	this->_vx = x;
}
void Vec2::y(const float y)
{
	this->_vy = y;
}
void Vec2::set(const float x, const float y)
{
	this->_vx = x;
	this->_vy = y;
}
void Vec2::set(const Vec2& inVec2)
{
	this->_vx = inVec2._vx;
	this->_vy = inVec2._vy;
}
void Vec2::set(const Vec3& inVec3)
{
	this->_vx = inVec3._vx;
	this->_vy = inVec3._vy;
}
void Vec2::set(const Vec4& inVec4)
{
	this->_vx = inVec4._vx;
	this->_vy = inVec4._vy;
}

Vec2 Vec2::operator+() const
{
	float x = this->_vx < 0 ? -1.0f * this->_vx : this->_vx;
	float y = this->_vy < 0 ? -1.0f * this->_vy : this->_vy;
	return Vec2(x, y);
}
Vec2 Vec2::operator+(const Vec2& inVec2) const
{
	return Vec2(this->_vx + inVec2._vx, this->_vy + inVec2._vy);
}
Vec2& Vec2::operator+=(const Vec2& inVec2)
{
	this->_vx += inVec2._vx;
	this->_vy += inVec2._vy;
	return *this;
}

Vec2 Vec2::operator-() const
{
	return Vec2(-1.0f * this->_vx, -1.0f * this->_vy);
}
Vec2 Vec2::operator-(const Vec2& inVec2) const
{
	return Vec2(this->_vx - inVec2._vx, this->_vy * inVec2._vy);
}
Vec2& Vec2::operator-=(const Vec2& inVec2)
{
	this->_vx -= inVec2._vx;
	this->_vy -= inVec2._vx;
	return *this;
}

Vec2 Vec2::operator*(const float scale) const
{
	return Vec2(this->_vx * scale, this->_vy * scale);
}
Vec2& Vec2::operator*=(const float scale)
{
	this->_vx *= scale;
	this->_vy *= scale;
	return *this;
}
Vec2 operator*(const float scale, const Vec2& inVec2)
{
	return Vec2(inVec2._vx * scale, inVec2._vy * scale);
}

Vec2& Vec2::norm()
{
	float mag = Trig::sqrt((this->_vx * this->_vx) + (this->_vy * this->_vy));
	this->_vx /= mag;
	this->_vy /= mag;
	return *this;
}
Vec2 Vec2::getNorm() const
{
	float mag = Trig::sqrt((this->_vx * this->_vx) + (this->_vy * this->_vy));
	return Vec2(this->_vx / mag, this->_vy / mag);
}
Vec2Proxy Vec2::len() const
{
	return Vec2Proxy(this->_vx, this->_vy);
}

bool Vec2::isEqual(const Vec2& v, const float epsilon) const
{
	return (this->_vx <= v._vx + epsilon && this->_vx >= v._vx - epsilon &&
		this->_vy <= v._vy + epsilon && this->_vy >= v._vy - epsilon);
}
bool Vec2::isZero(const float epsilon) const
{
	return (this->_vx <= epsilon && this->_vx >= 0 - epsilon &&
		this->_vy <= epsilon && this->_vy >= 0 - epsilon);
}

void Vec2::Print(const char* pName) const
{
	std::printf("%s: (%f, %f)", pName, this->_vx, this->_vy);
}
