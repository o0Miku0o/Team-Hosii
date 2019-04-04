#ifndef FIXEDPOINT
#define FIXEDPOINT
constexpr long Round(const double dVal)
{
	return (long)(dVal + 0.5);
}
constexpr long FixedPoint(const double dVal)
{
	return Round(dVal * (1 << 8));
}
constexpr long FixedPoint(const long lVal)
{
	return lVal * (1 << 8);
}
constexpr long FixedPoint(const unsigned long ulVal)
{
	return (long)ulVal * (1 << 8);
}
constexpr long FixedToLong(const long lFixedPointVal)
{
	return lFixedPointVal >> 8;
}
constexpr double FixedToDouble(const long lFixedPointVal)
{
	double dest = lFixedPointVal >> 8;
	long mask = 1 << (8 - 1);
	double digit = 0.5;
	for (int i = 0; i < 8; ++i) 
	{
		if (lFixedPointVal & mask) dest += digit;
		mask >>= 1;
		digit *= 0.5;
	}
	return dest;
}
constexpr long AddFixedPoint(const long lFixedPointVal1, const long lFixedPointVal2)
{
	return lFixedPointVal1 + lFixedPointVal2;
}
constexpr long SubFixedPoint(const long lFixedPointVal1, const long lFixedPointVal2)
{
	return lFixedPointVal1 - lFixedPointVal2;
}
constexpr long MulFixedPoint(const long lFixedPointVal1, const long lFixedPointVal2)
{
	return (lFixedPointVal1 * lFixedPointVal2) >> 8;
}
constexpr long DivFixedPoint(const long lFixedPointVal1, const long lFixedPointVal2)
{
	return (lFixedPointVal1 << 8) / lFixedPointVal2;
}
#endif
