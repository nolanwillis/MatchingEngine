#include "TimeAmount.h"

#include <assert.h>
#include <cstdio>
#include <stdexcept>
#include <limits>

TimeAmount::TimeAmount()
	:
	rawTime(0)
{}
TimeAmount::TimeAmount(const long long rawTime)
	:
	rawTime(rawTime)
{}
TimeAmount::TimeAmount(const Duration duration)
	: 
	rawTime(0)
{
	// 1 s  = 30,000,000
	// 1 ms = 30,000
	// 1 us = 30
	const long long ONE_RAW_SECOND = 30000000;

	switch (duration)
	{
	case Duration::ZERO:
		this->rawTime = 0;
		break;
	case Duration::ONE_SECOND:
		this->rawTime = ONE_RAW_SECOND;
		break;
	case Duration::ONE_MILLISECOND:
		this->rawTime = ONE_RAW_SECOND / 1000;
		break;
	case Duration::ONE_MICROSECOND:
		this->rawTime = ONE_RAW_SECOND / 1000000;
		break;
	case Duration::ONE_MINUTE:
		this->rawTime = 60 * ONE_RAW_SECOND;
		break;
	case Duration::ONE_HOUR:
		this->rawTime = 60 * 60 * ONE_RAW_SECOND;
		break;
	case Duration::SIXTY_FPS:
		this->rawTime = ONE_RAW_SECOND / 60;
		break;
	case Duration::THIRTY_FPS:
		this->rawTime = ONE_RAW_SECOND / 30;
		break;
	case Duration::MIN:
		this->rawTime = std::numeric_limits<long long>::min();
		break;
	case Duration::MAX:
		this->rawTime = std::numeric_limits<long long>::max();
		break;
	case Duration::DWORD:
		// This should never be reached.
		assert(false);
		this->rawTime = 0;
		break;
	default:
		// This should never be reached.
		assert(false);
		this->rawTime = 0;
		break;
	}
}
TimeAmount::TimeAmount(const TimeAmount& rhs)
	:
	rawTime(rhs.rawTime)
{}
TimeAmount& TimeAmount::operator=(const TimeAmount& rhs)
{
	// Check for self assignment.
	if (this != &rhs)
	{
		this->rawTime = rhs.rawTime;
	}
	return *this;
}

bool TimeAmount::operator==(const TimeAmount& rhs) const
{
	return(this->rawTime == rhs.rawTime);
}
bool TimeAmount::operator!=(const TimeAmount& rhs) const
{
	return(this->rawTime != rhs.rawTime);
}
bool TimeAmount::operator<(const TimeAmount& rhs) const
{
	return(this->rawTime < rhs.rawTime);
}
bool TimeAmount::operator<=(const TimeAmount& rhs) const
{
	return(this->rawTime <= rhs.rawTime);
}
bool TimeAmount::operator>(const TimeAmount& rhs) const
{
	return(this->rawTime > rhs.rawTime);
}
bool TimeAmount::operator>=(const TimeAmount& rhs) const
{
	return(this->rawTime >= rhs.rawTime);
}

const TimeAmount TimeAmount::operator+(const TimeAmount& rhs) const
{
	long long result = this->rawTime + rhs.rawTime;

	if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Addition overflow");
	}

	return(TimeAmount(result));
}
TimeAmount& TimeAmount::operator+=(const TimeAmount& rhs)
{
	long long result = this->rawTime + rhs.rawTime;

	if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Addition overflow");
	}

	this->rawTime = result;
	return(*this);
}

const TimeAmount TimeAmount::operator-(const TimeAmount& rhs) const
{
	long long result = this->rawTime - rhs.rawTime;
	
	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}

	return(TimeAmount(result));
}
TimeAmount& TimeAmount::operator-=(const TimeAmount& rhs)
{
	long long result = this->rawTime - rhs.rawTime;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}

	this->rawTime = result;
	return(*this);
}

const TimeAmount operator*(const int ratio, const TimeAmount& timeAmount)
{
	long long result = ratio * timeAmount.rawTime;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}
	else if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Multiplication overflow");
	}

	return(TimeAmount(result));
}
const TimeAmount TimeAmount::operator*(const TimeAmount& rhs) const
{
	long long result = this->rawTime * rhs.rawTime;

	if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Multiplication overflow");
	}

	return(TimeAmount(result));
}
const TimeAmount TimeAmount::operator*(const int rhs) const
{
	long long result = this->rawTime * rhs;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}
	else if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Multiplication overflow");
	}

	return(TimeAmount(result));
}
TimeAmount& TimeAmount::operator*=(const TimeAmount& rhs)
{
	long long result = this->rawTime * rhs.rawTime;

	if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Multiplication overflow");
	}

	this->rawTime = result;
	return(*this);
}
TimeAmount& TimeAmount::operator*=(const int rhs)
{
	long long result = this->rawTime * rhs;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}
	else if (result > std::numeric_limits<long long>::max())
	{
		throw std::overflow_error("Multiplication overflow");
	}

	this->rawTime = result;
	return(*this);
}

long long TimeAmount::operator/(const TimeAmount& denominator) const
{
	assert(denominator.rawTime != 0);

	return(this->rawTime / denominator.rawTime);
}
const TimeAmount TimeAmount::operator/(const int denominator) const
{
	assert(denominator != 0);

	long long result = this->rawTime / denominator;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}

	return(TimeAmount(result));
}
TimeAmount& TimeAmount::operator/=(const int denominator)
{
	assert(denominator != 0);

	long long result = this->rawTime / denominator;

	if (result < 0)
	{
		result = 0;
		std::printf("Result is 0. Negative time is not allowed.\n");
	}

	this->rawTime = result;
	return(*this);
}

long long TimeAmount::Quotient(const TimeAmount& numerator, const TimeAmount& denominator)
{
	assert(denominator.rawTime != 0);

	return(numerator.rawTime / denominator.rawTime);
}
const TimeAmount TimeAmount::Remainder(const TimeAmount& numerator, const TimeAmount& denominator)
{
	return(TimeAmount(numerator.rawTime % denominator.rawTime));
}


