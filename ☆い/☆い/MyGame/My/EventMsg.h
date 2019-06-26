#pragma once

#include "Stream.h"

class EventMsg
{
private:
	Stream<IOMode::IO_IN> is;
	std::string msg;
	int frame_count;
	int interval;
	size_t read_num;
public:
	EventMsg(const std::string &_filename, const int _interval = 1, const size_t _read_num = 1)
		: is(_filename)
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
	{

	}
	EventMsg(const int _interval = 1, const size_t _read_num = 1)
		: is()
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
	{

	}
	virtual ~EventMsg()
	{
		Close();
	}
	const bool Open(const std::string &_filename)
	{
		return is.Open(_filename);
	}
	const int Interval(const int _interval)
	{
		const int old = interval;
		interval = _interval;
		return old;
	}
	const int ReadNum(const size_t _read_num)
	{
		const size_t old = read_num;
		read_num = _read_num;
		return old;
	}
	const bool Run()
	{
		++frame_count;
		if (frame_count >= interval)
		{
			frame_count = 0;
			if (is.Eof()) return 1;
			std::string in;
			is.Read(in, read_num);
			msg += in;
		}
		return 0;
	}
	void Close()
	{
		is.Close();
	}
	const bool IsOpened() const
	{
		return is.IsOpened();
	}
	const std::string &Msg() const
	{
		return msg;
	}
};