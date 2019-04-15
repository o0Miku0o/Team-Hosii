#ifndef ARRAY
#define ARRAY
#include <malloc.h>
template<class Type>
class array
{
	Type *tpFront;
	Type *tpBack;
	size_t sDataSize;
public:
	array()
		:
		tpFront(nullptr),
		tpBack(nullptr),
		sDataSize(0)
	{
	}
	array(const array<Type> &aOther)
		:
		tpFront(nullptr),
		tpBack(nullptr),
		sDataSize(aOther.sDataSize)
	{
		const size_t sSize = sizeof(Type) * sDataSize;
		tpFront = (Type *)malloc(sSize);
		if (!tpFront) return;
		memcpy_s(tpFront, sSize, aOther.tpFront, sSize);
		tpBack = (tpFront + (sDataSize - 1));
	}
	~array()
	{
		clear();
	}
	Type * const begin() const
	{
		return tpFront;
	}
	const Type * const end() const
	{
		return (tpBack + 1);
	}
	Type &front() const
	{
		return *tpFront;
	}
	Type &back() const
	{
		return *tpBack;
	}
	const size_t size() const
	{
		return sDataSize;
	}
	const size_t capacity() const
	{
		return sDataSize * sizeof(Type);
	}
	void clear()
	{
		sDataSize = 0;
		if (!tpFront) return;
		free(tpFront);
		tpFront = nullptr;
	}
	const Type * const data() const
	{
		return tpFront;
	}
	const bool push_back(const Type &tData)
	{
		if (tpFront)
		{
			if (auto tpTmp = (Type *)realloc(tpFront, sizeof(Type) * (sDataSize + 1)))
			{
				tpFront = tpTmp;
			}
			else
			{
				return 1;
			}
			*(tpFront + sDataSize) = tData;
			tpBack = (tpFront + sDataSize);
			++sDataSize;
			return 0;
		}
		tpFront = (Type *)malloc(sizeof(Type) * 1);
		if (!tpFront) return 1;
		*tpFront = tData;
		tpBack = tpFront;
		sDataSize = 1;
		return 0;
	}
	const Type &operator [] (const size_t sIdx) const
	{
		if (sIdx < sDataSize)
		{
			return *(tpFront + sIdx);
		}
		MessageBox(nullptr, "ptr referenced out of range !", "warning !", MB_OK | MB_ICONWARNING);
		if (tpFront) free(tpFront);
		exit(1);
	}
};
#endif