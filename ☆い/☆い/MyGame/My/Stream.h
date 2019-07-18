#pragma once

#undef max

#include <Windows.h>
#include <fstream>
#include <string>

enum IOMode
{
	IO_IN,
	IO_OUT,
};

template<IOMode>
class Stream;

template<>
class Stream<IOMode::IO_IN>
{
private:
	std::ifstream is;
	bool res;
public:
	Stream()
		: is()
		, res(false)
	{
		
	}
	Stream(const std::string &_filename)
		: is(_filename)
		, res(true)
	{
		if (!is) res = false;
	}
	virtual ~Stream()
	{
		Close();
	}
	const bool Open(const std::string &_filename)
	{
		Close();
		is.open(_filename);
		if (!is)
		{
			res = false;
			return 0;
		}
		res = true;
		return 1;
	}
	void Close()
	{
		if (IsOpened()) is.close();
	}
	template<class In>
	Stream<IOMode::IO_IN> &operator >> (In &_in)
	{
		if (!IsOpened())
		{
			MessageBox(nullptr, "file is not opend !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		if (is.eof())
		{
			MessageBox(nullptr, "end of file !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		is >> _in;
		return *this;
	}
	template<class In>
	Stream<IOMode::IO_IN> &Get(In &_in)
	{
		if (!IsOpened())
		{
			MessageBox(nullptr, "file is not opend !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		if (is.eof())
		{
			MessageBox(nullptr, "end of file !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		_in = (In)is.get();
		return *this;
	}
	Stream<IOMode::IO_IN> &Read(std::string &_in, const size_t _num)
	{
		char *_buf = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(char) * (_num + 1));
		if (!_buf)
		{
			MessageBox(nullptr, "buffer is null !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		is.read(_buf, _num);
		_in = _buf;
		HeapFree(GetProcessHeap(), 0, _buf);
		return *this;
	}
	Stream<IOMode::IO_IN> &Ignore(const char _ignore)
	{
		is.ignore(std::numeric_limits<std::streamsize>::max(), _ignore);
		return *this;
	}
	const bool IsOpened() const
	{
		return res;
	}
	const bool Eof() const
	{
		return is.eof();
	}
	template<class Out>
	Stream<IOMode::IO_IN> &operator << (Out &_out) = delete;
};

template<>
class Stream<IOMode::IO_OUT>
{
private:
	std::ofstream os;
	bool res;
public:
	Stream()
		: os()
		, res(false)
	{

	}
	Stream(const std::string &_filename)
		: os(_filename)
		, res(true)
	{
		if (!os) res = false;
	}
	virtual ~Stream()
	{
		Close();
	}
	const bool Open(const std::string &_filename)
	{
		Close();
		os.open(_filename);
		if (!os)
		{
			res = false;
			return 0;
		}
		res = true;
		return 1;
	}
	void Close()
	{
		if (IsOpened()) os.close();
	}
	template<class Out>
	Stream<IOMode::IO_OUT> &operator << (Out &_out)
	{
		if (!IsOpened())
		{
			MessageBox(nullptr, "file is not opend !", nullptr, MB_OK | MB_ICONWARNING);
			return *this;
		}
		os << _out;
		return *this;
	}
	const bool IsOpened() const
	{
		return res;
	}
	template<class In>
	Stream<IOMode::IO_OUT> &operator >> (In &_in) = delete;
};