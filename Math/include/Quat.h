#ifndef MATH_QUAT_H
#define MATH_QUAT_H

#include "Enum.h"
#include "Vec3.h"
#include "Vec4.h"

class Rot;
class Scale;
class Trans;

class Quat 
{
public:
	friend class Mat3;
	friend class Mat4;
	friend class Rot;

	Quat();
	Quat(const Quat& qIn);
	Quat(const Vec3& vec, const float real);	
	Quat(const float vx, const float vy, const float vz, const float real);
	explicit Quat(const enum Identity_enum);
	explicit Quat(const Rot& rot);		
	Quat(const Rot1 type, const float angle_radians);
	Quat(const Rot3 type, const float angle_x, const float angle_y, const float angle_z);
	Quat(const Axis type, const Vec3& vAxis, const float angle_radians);
	Quat(const Orient orient, const Vec3& dof, const Vec3& up);
	Quat& operator=(const Quat& q);
	Quat& operator=(const Rot& rot);
	~Quat() = default;

	void set(const enum Identity_enum);
	void set(const Rot& rot);
	void set(const Rot1 type, const float angle);
	void set(const Rot3 type, const float angle_x, const float angle_y, 
		const float angle_z);
	void set(const Axis type, const Vec3& vAxis, const float angle_radians);
	void set(const Orient orient, const Vec3& dof, const Vec3& up);
	void set(const float vx, const float vy, const float vz, const float real);
	void set(const Vec3& vect, const float real);
	void setVec3(const Vec3& vect);
	
	void qx(const float vx);
	void qy(const float vy);
	void qz(const float vz);
	void real(const float real);

	float& operator[](const x_enum value);
	float& operator[](const y_enum value);
	float& operator[](const z_enum value);
	float& operator[](const w_enum value);
	float operator[](const x_enum value) const;
	float operator[](const y_enum value) const;	
	float operator[](const z_enum value) const;
	float operator[](const w_enum value) const;

	float qx() const;
	float qy() const;
	float qz() const;
	float real() const;

	float getAngle() const;
	void getVec3(Vec3& vOut) const;
	void getAxis(Vec3& vOut) const;

	float dot(const Quat& qin) const;
	float mag() const;
	float magSquared() const;
	float invMag() const;
	Quat& conj();
	Quat getConj() const;
	Quat& inv();
	Quat getInv() const;
	Quat& norm();
	Quat getNorm() const;

	// Linear Operator: vOut = Quat * Vector * Quat*		
	void Lqvqc(const Vec3& vIn, Vec3& vOut) const;
	// Linear Operator:  vOut = Quat* * Vector * Quat		
	void Lqcvq(const Vec3& vIn, Vec3& vOut) const;

	bool isEqual(const Quat& qin, const float epsilon = MATH_TOLERANCE) const;
	bool isEquivalent(const Quat& qin, const float epsilon = MATH_TOLERANCE) const;
	bool isNegEqual(const Quat& qin, const float epsilon = MATH_TOLERANCE) const;
	bool isConjugateEqual(const Quat& qin, const float epsilon = MATH_TOLERANCE) const;
	bool isIdentity(const float epsilon = MATH_TOLERANCE) const;
	bool isNormalized(const float epsilon = MATH_TOLERANCE) const;

	Quat operator+() const;
	Quat operator+(const Quat& q) const;
	Quat& operator+=(const Quat& q);
	Quat operator+(const float a) const;
	Quat& operator+=(const float a);
	friend Quat operator+(const float a, const Quat& q);

	Quat operator-() const;
	Quat operator-(const Quat& q) const;
	Quat& operator-=(const Quat& q);
	Quat operator-(const float a) const;
	Quat& operator-=(const float a);
	friend Quat operator-(const float a, const Quat& q);

	Quat operator*(const Quat& q) const;
	Quat& operator*=(const Quat& q);
	Quat operator*(const float a) const;
	Quat& operator*=(const float a);
	Mat4 operator*(const Mat4& m) const;
	Quat& operator*=(const Mat4& m) = delete;
	Mat4 operator*(const Scale& m) const;
	Mat4& operator*=(const Scale& m) = delete;
	Rot operator*(const Rot& m) const;
	Quat& operator*=(const Rot& m);
	Mat4 operator*(const Trans& m) const;
	Mat4& operator*=(const Trans& m) = delete;
	friend Quat operator*(const float a, const Quat &q);

	Quat operator/(const Quat& q) const;
	Quat& operator/=(const Quat& q);
	Quat operator/(const float a) const;
	Quat& operator/=(const float a);
	friend Quat operator/(const float a, const Quat& q);

	//	void Print(const char *pName) const;

private:
	union
	{
		__m128	_mq;
		
		struct
		{
			float _qx;
			float _qy;
			float _qz;
			float _qw;
		};
		
		struct
		{
			Vec3  _qV3;
		};
		
		struct
		{
			Vec4 _qV4;
		};
	};
};

#endif 
