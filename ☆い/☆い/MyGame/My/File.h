#pragma once

#include <Windows.h>
#include <fstream>
#include <string>

enum OpenMode
{
	FM_IN = 1,
	FM_OUT = 2,
};

template<OpenMode>
class File;

template<>
class File<OpenMode::FM_IN>
{
private:
	std::fstream fFileStream;
	bool bResult;

	const bool IsOpend() const
	{
		return bResult;
	}
public:
	File()
		: fFileStream()
		, bResult(false)
	{

	}
	File(const std::string &asFileName)
		: fFileStream(asFileName, OpenMode::FM_IN)
		, bResult(true)
	{
		if (!fFileStream) bResult = false;
	}
	virtual ~File()
	{
		if (IsOpend()) Close();
	}
	const bool Open(const std::string &asFileName)
	{
		if (IsOpend()) Close();
		fFileStream.open(asFileName, OpenMode::FM_IN);
		if (!fFileStream)
		{
			bResult = false;
			return 1;
		}
		return 0;
	}
	void Close()
	{
		fFileStream.close();
	}
	template<class In>
	File<OpenMode::FM_IN> &operator >> (In &in)
	{
		try
		{
			if (!IsOpend()) throw "file is not opend !";
			fFileStream >> in;
		}
		catch (const char *cpError)
		{
			MessageBox(nullptr, cpError, nullptr, MB_OK | MB_ICONWARNING);
			exit(EXIT_FAILURE);
		}
		return *this;
	}
	template<class Out>
	File<OpenMode::FM_IN> &operator << (Out &out) = delete;
};

template<>
class File<OpenMode::FM_OUT>
{
	std::fstream fFileStream;
	bool bResult;

	const bool IsOpend() const
	{
		return bResult;
	}
public:
	File()
		: fFileStream()
		, bResult(false)
	{

	}
	File(const std::string &asFileName)
		: fFileStream(asFileName, OpenMode::FM_OUT)
		, bResult(true)
	{
		if (!fFileStream) bResult = false;
	}
	virtual ~File()
	{
		if (IsOpend()) Close();
	}
	const bool Open(const std::string &asFileName)
	{
		if (IsOpend()) Close();
		fFileStream.open(asFileName, OpenMode::FM_OUT);
		if (!fFileStream)
		{
			bResult = false;
			return 1;
		}
		return 0;
	}
	void Close()
	{
		fFileStream.close();
	}
	template<class Out>
	File<OpenMode::FM_OUT> &operator << (Out &out)
	{
		try
		{
			if (!IsOpend()) throw "file is not opend !";
			fFileStream << out;
		}
		catch (const char *cpError)
		{
			MessageBox(nullptr, cpError, nullptr, MB_OK | MB_ICONWARNING);
			exit(EXIT_FAILURE);
		}
		return *this;
	}
	template<class In>
	File<OpenMode::FM_OUT> &operator >> (In &in) = delete;
};