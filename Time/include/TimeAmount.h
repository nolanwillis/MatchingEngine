#ifndef TIME_AMOUNT_H
#define TIME_AMOUNT_H
 
/*
Class that represents an amount of time. Serves as an abstract data type that encapsulates 
a long long int variable called rawTime, the actual numeric length of time as an integer. One 
second is equal to the value of 30,000,000.
*/
class TimeAmount
{
public:
	enum class Duration
	{
		// For constructing a time amount of zero. 
		ZERO,
		// For constructing a time amount of one microsecond. 
		ONE_MICROSECOND,
		// For constructing a time amount of one millisecond. 
		ONE_MILLISECOND,
		// For constructing a time amount of one second. 
		ONE_SECOND,
		// For constructing a time amount of one minute. 
		ONE_MINUTE,
		// For constructing a time amount of one hour. 
		ONE_HOUR,
		// For constructing a time amount equal to the frame time of 60 fps.
		SIXTY_FPS,
		// For constructing a time amount equal to the frame time of 30 fps.
		THIRTY_FPS,
		// For constructing a time amount of the most negative time that can be represented.
		MIN,
		// For constructing a time period of most positive time that can be represented.
		MAX,
		// Ensure the enum is the size of an int. This should never be used.
		DWORD = 0x7FFFFFFF
	};

	TimeAmount();
	TimeAmount(const Duration duration);
	TimeAmount(const TimeAmount& rhs);
	TimeAmount& operator=(const TimeAmount& rhs);
	~TimeAmount() = default;
	
	bool operator==(const TimeAmount& rhs) const;
	bool operator!=(const TimeAmount& rhs) const;
	bool operator<(const TimeAmount& rhs) const;
	bool operator<=(const TimeAmount& rhs) const;
	bool operator>(const TimeAmount& rhs) const;
	bool operator>=(const TimeAmount& rhs) const;

	const TimeAmount operator+(const TimeAmount& rhs) const;
	TimeAmount& operator+=(const TimeAmount& rhs);
	const TimeAmount operator-(const TimeAmount& rhs) const;
	TimeAmount& operator-=(const TimeAmount& rhs);
	
	// Required for int * TimeAmount.
	friend const TimeAmount operator*(const int ratio, const TimeAmount& timeAmount);
	const TimeAmount operator*(const TimeAmount& rhs) const;
	const TimeAmount operator*(const int rhs) const;
	TimeAmount& operator*=(const TimeAmount& rhs);
	TimeAmount& operator*=(const int rhs);

	long long operator/(const TimeAmount& denominator) const;
	const TimeAmount operator/(const int denominator) const;
	TimeAmount& operator/=(const int);

	// Returns the truncated, integral division of the numerator and denominator.
	// In other words, the result of the division is rounded down to the nearest
	// integer. Dividing by TimeAmount(ZERO) is undefined.
	static long long Quotient(const TimeAmount& numerator, const TimeAmount& denominator);
	// Returns the remainder of dividing the numerator into the denominator. This 
	// is the equivalent of a modulus operation. 
	static const TimeAmount Remainder(const TimeAmount& numerator, const TimeAmount& denominator);

private:
	long long rawTime;
	
	TimeAmount(const long long rawTime);
};

#endif  
