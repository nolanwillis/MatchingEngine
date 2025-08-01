#ifndef MATH_VEC2_PROXY_H
#define MATH_VEC2_PROXY_H

struct Vec2Proxy
{
public:
	Vec2Proxy(float x, float y);
	Vec2Proxy() = delete;
	Vec2Proxy(const Vec2Proxy& rhs) = default;
	Vec2Proxy& operator = (const Vec2Proxy& rhs) = default;
	~Vec2Proxy() = default;

	operator float() const;

	float operator * (const Vec2Proxy& rhs) const;

	bool operator > (const Vec2Proxy& rhs) const;
	bool operator < (const Vec2Proxy& rhs) const;
	bool operator == (const Vec2Proxy& rhs) const;
	bool operator >= (const Vec2Proxy& rhs) const;
	bool operator <= (const Vec2Proxy& rhs) const;
	bool operator != (const Vec2Proxy& rhs) const;

private:
	float x;
	float y;
};

#endif
