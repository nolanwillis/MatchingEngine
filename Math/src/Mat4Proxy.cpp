#include "Mat4Proxy.h"
#include "Mat4.h"

Mat4Proxy::Mat4Proxy(Mat4& matrix, float& value)
	: matrix(matrix), value(value)
{}

Mat4Proxy Mat4Proxy::operator=(float r)
{
	this->value = r;
	matrix._u_m15 &= (unsigned int)(0xFFFFFFF8);
	return *this;
}

Mat4Proxy::operator float()
{
	return this->value;
}
