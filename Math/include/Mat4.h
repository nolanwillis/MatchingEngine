#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "Constants.h"
#include "Enum.h"
#include "Mat4Proxy.h"
#include "Vec4.h"

class Quat;
class Rot;
class Scale;
class Trans;

class Mat4
{
public:
	friend class Mat3;
	friend class Mat4Proxy;
	friend class Rot;
	friend class Scale;
	friend class Trans;
	friend class Vec4;

	enum class Hint
	{
		Generalize = 0x0,        // generalize 4x4 inverse  (no flags)
		Rot = 0x1,               // matrix inverse is M.T()
		Trans = 0x2,             // matrix inverse is M(-trans)
		RotTrans = 0x3,          // rot and trans  A_inv is A.T() 
		Scale = 0x4,             // matrix invers is M(1/scale)
		RotScale = 0x5,          // Rot and Scale no translate
		TransScale = 0x6,        // Trans and Scale no Translate
		Affine = 0x7             // generalize Affine
	};

	inline void privClearHint()
	{
		this->_u_m15 &= (unsigned int)(0xFFFFFFF8);
	}
	inline void privSetGeneralHint()
	{
		this->_u_m15 &= (unsigned int)(0xFFFFFFF8);
	}
	inline void privSetScaleHint()
	{
		this->_u_m15 |= (unsigned int)(Hint::Scale);
	}
	inline void privSetRotHint()
	{
		this->_u_m15 |= (unsigned int)(Hint::Rot);
	}
	inline void privSetTransHint()
	{
		this->_u_m15 |= (unsigned int)(Hint::Trans);
	}
	inline void privSetCopyHint() const
	{
		// do nothing
	}
	inline Hint privGetHint() const
	{
		Hint h;

		// test if m15 ~= 1.0f (ignore last 3 bits flags, actually 8 bits to account for noise)

		if ((this->_u_m15 & 0xFFFFFF00) == 0x3f800000 ||
			(this->_u_m15 & 0xFFFFFF00) == 0x3f7fff00)
		{
			h = (Hint)(this->_u_m15 & 0x7);
		}
		else
		{
			h = Hint::Generalize;
		}

		return h;
	}
	inline void privSetNewHint(Hint A, Hint B)
	{
		Hint h;

		if (A == Hint::Generalize || B == Hint::Generalize)
		{
			h = Hint::Generalize;
		}
		else // hint isn't a generalized matrix
		{
			h = (Hint)((unsigned int)A | (unsigned int)B);
		}

		// Set it.
		this->_u_m15 &= (unsigned int)0xFFFFFFF8;
		this->_u_m15 |= (unsigned int)h;
	}

	Mat4();
	explicit Mat4(const enum Identity_enum);
	Mat4(const Vec4& tV0, const Vec4& tV1, const Vec4& tV2, const Vec4& tV3);
	Mat4(const Mat4& m);
	Mat4& operator = (const Mat4& m);
	Mat4(Mat4&&) = default;
	Mat4& operator = (Mat4&&) = default;
	explicit Mat4(const Quat& q);
	~Mat4() = default;

	Mat4Proxy operator[] (const enum m0_enum);
	Mat4Proxy operator[] (const enum m1_enum);
	Mat4Proxy operator[] (const enum m2_enum);
	Mat4Proxy operator[] (const enum m3_enum);
	Mat4Proxy operator[] (const enum m4_enum);
	Mat4Proxy operator[] (const enum m5_enum);
	Mat4Proxy operator[] (const enum m6_enum);
	Mat4Proxy operator[] (const enum m7_enum);
	Mat4Proxy operator[] (const enum m8_enum);
	Mat4Proxy operator[] (const enum m9_enum);
	Mat4Proxy operator[] (const enum m10_enum);
	Mat4Proxy operator[] (const enum m11_enum);
	Mat4Proxy operator[] (const enum m12_enum);
	Mat4Proxy operator[] (const enum m13_enum);
	Mat4Proxy operator[] (const enum m14_enum);
	Mat4Proxy operator[] (const enum m15_enum);

	float operator[] (const enum m0_enum) const;
	float operator[] (const enum m1_enum) const;
	float operator[] (const enum m2_enum) const;
	float operator[] (const enum m3_enum) const;
	float operator[] (const enum m4_enum) const;
	float operator[] (const enum m5_enum) const;
	float operator[] (const enum m6_enum) const;
	float operator[] (const enum m7_enum) const;
	float operator[] (const enum m8_enum) const;
	float operator[] (const enum m9_enum) const;
	float operator[] (const enum m10_enum) const;
	float operator[] (const enum m11_enum) const;
	float operator[] (const enum m12_enum) const;
	float operator[] (const enum m13_enum) const;
	float operator[] (const enum m14_enum) const;
	float operator[] (const enum m15_enum) const;

	void set(const Mat4& mIn);
	void set(const Vec4& V0, const Vec4& V1, const Vec4& V2, const Vec4& V3);
	void set(const enum Identity_enum);
	void set(const Row4 type, const Vec4& V);
	void set(const Quat& qIn);
	Vec4 get(const Row4 type) const;

	void m0(const float v);
	void m1(const float v);
	void m2(const float v);
	void m3(const float v);
	void m4(const float v);
	void m5(const float v);
	void m6(const float v);
	void m7(const float v);
	void m8(const float v);
	void m9(const float v);
	void m10(const float v);
	void m11(const float v);
	void m12(const float v);
	void m13(const float v);
	void m14(const float v);
	void m15(const float v);

	float m0() const;
	float m1() const;
	float m2() const;
	float m3() const;
	float m4() const;
	float m5() const;
	float m6() const;
	float m7() const;
	float m8() const;
	float m9() const;
	float m10() const;
	float m11() const;
	float m12() const;
	float m13() const;
	float m14() const;
	float m15() const;

	float det() const;
	Mat4& T(void);
	Mat4 getT(void)const;
	Mat4 getInv(void) const;
	Mat4& inv(void);

	Mat4 operator + (void) const;
	Mat4 operator + (const Mat4& A) const;
	Mat4& operator += (const Mat4& A);

	Mat4 operator - (void) const;
	Mat4 operator - (const Mat4& A) const;
	Mat4& operator -= (const Mat4& A);

	Mat4 operator * (const float s) const;
	Mat4& operator *= (const float scale);
	Mat4 operator * (const Mat4& A) const;
	Mat4& operator *= (const Mat4& A);
	Mat4 operator * (const Scale& A) const;
	Mat4& operator *= (const Scale& A);
	Mat4 operator * (const Rot& A) const;
	Mat4& operator *= (const Rot& A);
	Mat4 operator * (const Trans& A) const;
	Mat4& operator *= (const Trans& A);
	friend Mat4 operator *(const float scale, const Mat4& A);
	Mat4 operator * (const Quat& q) const;
	Mat4 operator *= (const Quat& q);

	bool isEqual(const Mat4& A, const float epsilon = MATH_TOLERANCE) const;
	bool isIdentity(const float epsilon = MATH_TOLERANCE) const;
	bool isRotation(const float epsilon = MATH_TOLERANCE) const;

	void Print(const char* pName) const;

protected:
	union
	{
		/*     | m0  m1  m2   m3  | */
		/* m = | m4  m5  m6   m7  | */
		/*     | m8  m9  m10  m11 | */
		/*     | m12 m13 m14  m15 | */

		struct
		{
			Vec4 _rows[4];
		};

		struct
		{
			Vec4 _v0;
			Vec4 _v1;
			Vec4 _v2;
			Vec4 _v3;
		};

		struct
		{
			float _m0;
			float _m1;
			float _m2;
			float _m3;
			float _m4;
			float _m5;
			float _m6;
			float _m7;
			float _m8;
			float _m9;
			float _m10;
			float _m11;
			float _m12;
			float _m13;
			float _m14;
			union
			{
				float _m15;
				unsigned int _u_m15;
			};
		};
	};

private:
	Mat4 GetGeneralInv() const;
	Mat4 GetAffineInv() const;
	Mat4 GetRotInv() const;
	Mat4 GetScaleInv() const;
	Mat4 GetTransInv() const;
	Mat4 GetRotScaleInv() const;
	Mat4 GetRotTransInv() const;
	Mat4 GetTransScaleInv() const;

	void GeneralInv();
	void AffineInv();
	void RotInv();
	void ScaleInv();
	void TransInv();
	void RotScaleInv();
	void RotTransInv();
	void TransScaleInv();
};

#endif
