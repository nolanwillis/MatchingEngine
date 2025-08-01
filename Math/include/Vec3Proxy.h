#ifndef MATH_VEC3_PROXY_H
#define MATH_VEC3_PROXY_H

struct Vec3Proxy
{
public:
	Vec3Proxy(float x, float y, float z);
	Vec3Proxy() = delete;
	Vec3Proxy(const Vec3Proxy&) = default;
	Vec3Proxy& operator = (const Vec3Proxy&) = default;
	~Vec3Proxy() = default;

	operator float() const;

	float operator * (const Vec3Proxy& r) const;

	bool operator > (const Vec3Proxy& r) const;
	bool operator < (const Vec3Proxy& r) const;
	bool operator == (const Vec3Proxy& r) const;
	bool operator >= (const Vec3Proxy& r) const;
	bool operator <= (const Vec3Proxy& r) const;
	bool operator != (const Vec3Proxy& r) const;

private:
	float x;
	float y;
	float z;
};

#endif
