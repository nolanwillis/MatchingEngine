#ifndef MATH_MAT4_PROXY_H
#define MATH_MAT4_PROXY_H

class Mat4;

struct Mat4Proxy
{
	Mat4Proxy(Mat4& matrix, float& value);

	Mat4Proxy operator = (float r);
	operator float();

	Mat4& matrix;
	float& value;
};

#endif
