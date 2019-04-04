#ifndef FIXEDPOINT
#define FIXEDPOINT
inline constexpr long Round(const double dVal)
{
	return (long)(dVal + 0.5);
}
inline constexpr long FP(const double dVal)
{
	return Round(dVal * (1 << 8));
}
inline constexpr long FP(const long lVal)
{
	return lVal * (1 << 8);
}
inline constexpr long FP(const unsigned long ulVal)
{
	return (long)ulVal * (1 << 8);
}
inline constexpr long FToL(const long lFPVal)
{
	return lFPVal >> 8;
}
inline constexpr double FToD(const long lFPVal)
{
	double dest = lFPVal >> 8;
	long mask = 1 << (8 - 1);
	double digit = 0.5;
	for (int i = 0; i < 8; ++i) 
	{
		if (lFPVal & mask) dest += digit;
		mask >>= 1;
		digit *= 0.5;
	}
	return dest;
}
inline constexpr long AddFP(const long lFPVal1, const long lFPVal2)
{
	return lFPVal1 + lFPVal2;
}
inline constexpr long SubFP(const long lFPVal1, const long lFPVal2)
{
	return lFPVal1 - lFPVal2;
}
inline constexpr long MulFP(const long lFPVal1, const long lFPVal2)
{
	return (lFPVal1 * lFPVal2) >> 8;
}
inline constexpr long DivFP(const long lFPVal1, const long lFPVal2)
{
	return (lFPVal1 << 8) / lFPVal2;
}

template<unsigned short DBits>
inline constexpr long FP(const double dVal)
{
	return Round(dVal * (1 << DBits));
}
template<unsigned short DBits>
inline constexpr long FP(const long lVal)
{
	return lVal * (1 << DBits);
}
template<unsigned short DBits>
inline constexpr long FP(const unsigned long ulVal)
{
	return (long)ulVal * (1 << DBits);
}
template<unsigned short DBits>
inline constexpr long FToL(const long lFPVal)
{
	return lFPVal >> DBits;
}
template<unsigned short DBits>
inline constexpr double FToD(const long lFPVal)
{
	double dest = lFPVal >> DBits;
	long mask = 1 << (DBits - 1);
	double digit = 0.5;
	for (int i = 0; i < DBits; ++i)
	{
		if (lFPVal & mask) dest += digit;
		mask >>= 1;
		digit *= 0.5;
	}
	return dest;
}
template<unsigned short DBits>
inline constexpr long MulFP(const long lFPVal1, const long lFPVal2)
{
	return (lFPVal1 * lFPVal2) >> DBits;
}
template<unsigned short DBits>
inline constexpr long DivFP(const long lFPVal1, const long lFPVal2)
{
	return (lFPVal1 << DBits) / lFPVal2;
}

constexpr short MAX_FLOAT16 = 1 << (16 - 6);
/*
２バイト、小数ビット数６の固定小数型
*/
struct fixed16
{
private:
	/*内部整数変数*/
	short sVal;
public:
	/*コンストラクタ*/
	fixed16()
		:
		sVal(0)
	{

	}
	fixed16(const fixed16 &f)
		:
		sVal(f.sVal)
	{

	}
	fixed16(const float f)
		:
		sVal((short)FP<6>((double)f))
	{

	}
	fixed16(const double d)
		:
		sVal((short)FP<6>(d))
	{

	}
	/*同型との演算*/
	inline fixed16 &operator = (const fixed16 &f)
	{
		sVal = f.sVal;
		return *this;
	}
	inline const float operator + (const fixed16 &f) const
	{
		return (float)FToD<6>(AddFP((long)sVal, (long)f.sVal));
	}
	inline const float operator - (const fixed16 &f) const
	{
		return (float)FToD<6>(SubFP((long)sVal, (long)f.sVal));
	}
	inline const float operator * (const fixed16 &f) const
	{
		return (float)FToD<6>(MulFP<6>((long)sVal, (long)f.sVal));
	}
	inline const float operator / (const fixed16 &f) const
	{
		return (float)FToD<6>(DivFP<6>((long)sVal, (long)f.sVal));
	}
	inline fixed16 &operator += (const fixed16 &f)
	{
		sVal = (short)AddFP((long)sVal, (long)f.sVal);
		return *this;
	}
	inline fixed16 &operator -= (const fixed16 &f)
	{
		sVal = (short)SubFP((long)sVal, (long)f.sVal);
		return *this;
	}
	inline fixed16 &operator *= (const fixed16 &f)
	{
		sVal = (short)MulFP<6>((long)sVal, (long)f.sVal);
		return *this;
	}
	inline fixed16 &operator /= (const fixed16 &f)
	{
		sVal = (short)DivFP<6>((long)sVal, (long)f.sVal);
		return *this;
	}
	/*float型との演算*/
	inline fixed16 &operator = (const float f)
	{
		sVal = (short)FP((double)f);
		return *this;
	}
	inline const float operator + (const float f) const
	{
		return (float)FToD<6>(AddFP((long)sVal, FP<6>((double)f)));
	}
	inline const float operator - (const float f) const
	{
		return (float)FToD<6>(SubFP((long)sVal, FP<6>((double)f)));
	}
	inline const float operator * (const float f) const
	{
		return (float)FToD<6>(MulFP<6>((long)sVal, FP<6>((double)f)));
	}
	inline const float operator / (const float f) const
	{
		return (float)FToD<6>(DivFP<6>((long)sVal, FP<6>((double)f)));
	}
	inline fixed16 &operator += (const float f)
	{
		sVal = (short)AddFP((long)sVal, FP<6>((double)f));
		return *this;
	}
	inline fixed16 &operator -= (const float f)
	{
		sVal = (short)SubFP((long)sVal, FP<6>((double)f));
		return *this;
	}
	inline fixed16 &operator *= (const float f)
	{
		sVal = (short)MulFP<6>((long)sVal, FP<6>((double)f));
		return *this;
	}
	inline fixed16 &operator /= (const float f)
	{
		sVal = (short)DivFP<6>((long)sVal, FP<6>((double)f));
		return *this;
	}
	/*double型との演算*/
	inline fixed16 &operator = (const double d)
	{
		sVal = (short)FP(d);
		return *this;
	}
	inline const double operator + (const double d) const
	{
		return FToD<6>(AddFP((long)sVal, FP<6>(d)));
	}
	inline const double operator - (const double d) const
	{
		return FToD<6>(SubFP((long)sVal, FP<6>(d)));
	}
	inline const double operator * (const double d) const
	{
		return FToD<6>(MulFP<6>((long)sVal, FP<6>(d)));
	}
	inline const double operator / (const double d) const
	{
		return FToD<6>(DivFP<6>((long)sVal, FP<6>(d)));
	}
	inline fixed16 &operator += (const double d)
	{
		sVal = (short)AddFP((long)sVal, FP<6>(d));
		return *this;
	}
	inline fixed16 &operator -= (const double d)
	{
		sVal = (short)SubFP((long)sVal, FP<6>(d));
		return *this;
	}
	inline fixed16 &operator *= (const double d)
	{
		sVal = (short)MulFP<6>((long)sVal, FP<6>(d));
		return *this;
	}
	inline fixed16 &operator /= (const double d)
	{
		sVal = (short)DivFP<6>((long)sVal, FP<6>(d));
		return *this;
	}
	/*インクリメント演算子*/
	inline fixed16 &operator ++ ()
	{
		sVal = (short)AddFP((long)sVal, FP<6>(1.0));
		return *this;
	}
	/*デクリメント演算子*/
	inline fixed16 &operator -- ()
	{
		sVal = (short)SubFP((long)sVal, FP<6>(1.0));
		return *this;
	}
	/*インクリメント演算子*/
	inline const fixed16 operator ++ (int)
	{
		const auto f = *this;
		sVal = (short)AddFP((long)sVal, FP<6>(1.0));
		return f;
	}
	/*デクリメント演算子*/
	inline const fixed16 operator -- (int)
	{
		const auto f = *this;
		sVal = (short)SubFP((long)sVal, FP<6>(1.0));
		return f;
	}
	/*float型へのキャスト*/
	inline operator float() const
	{
		return (float)FToD<6>((long)sVal);
	}
	/*double型へのキャスト*/
	inline operator double() const
	{
		return FToD<6>((long)sVal);
	}
};
#endif