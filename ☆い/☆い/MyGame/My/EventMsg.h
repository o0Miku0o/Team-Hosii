#pragma once

#include "My.h"
#include "Stream.h"

class EventMsg
{
public:
	enum Result
	{
		RES_FAILURE,
		RES_SUCCESS,
		RES_EOF,
	};
private:
	Image font;
	Stream<IOMode::IO_IN> is;
	Rec draw;
	std::string msg;
	int frame_count;
	int interval;
	size_t read_num;
public:
	EventMsg(const std::string &_filename, const int _interval = 1, const size_t _read_num = 1)
		: font()
		, is(_filename)
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
	{
		font.ImageCreate("./data/image/font/myfont.bmp");
	}
	EventMsg(const int _interval = 1, const size_t _read_num = 1)
		: font()
		, is()
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
	{
		font.ImageCreate("./data/image/font/myfont.bmp");
	}
	virtual ~EventMsg()
	{
		Close();
		font.Release();
	}
	const Result Open(const std::string &_filename)
	{
		return (is.Open(_filename)) ? Result::RES_SUCCESS : Result::RES_FAILURE;
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
	const Result Run()
	{
		++frame_count;
		if (frame_count >= interval)
		{
			frame_count = 0;
			if (is.Eof()) return Result::RES_EOF;
			std::string in;
			is.Read(in, read_num);
			/*アスキーコード読み込みなら*/
			if (in.length() == 1)
			{
				auto CmdComp = [&in](const char _r)
				{
					return in.at(0) == _r;
				};
				if (CmdComp('['))
				{
					std::string interval_string;
					is.Get(interval_string, ']');
					interval = atoi(interval_string.c_str());
					return Result::RES_SUCCESS;
				}
			}
			msg += in;
		}
		return Result::RES_SUCCESS;
	}
	void DrawAscii(const Point &_pos, const float _width, const float _height)
	{
		Frec src(0.f, 0.f, 6.f, 12.f);
		draw.Scaling(_width, _height);
		for (size_t i = 0; i < msg.size(); ++i)
		{
			Point d_pos = _pos;
			d_pos.x += i * _width;
			draw.SetPos(&d_pos);
			src.l = (msg.at(i) % 32) * 6.f;
			src.t = (msg.at(i) / 32) * 12.f;
			draw.Draw(&font, &src, false);
		}
	}
	void Clear()
	{
		msg.clear();
		is.Clear();
		is.Seek(0);
	}
	void Close()
	{
		is.Close();
	}
	const Result IsOpened() const
	{
		return (is.IsOpened()) ? Result::RES_SUCCESS : Result::RES_FAILURE;
	}
	const std::string &Msg() const
	{
		return msg;
	}
	const size_t Length() const
	{
		return msg.length();
	}
};