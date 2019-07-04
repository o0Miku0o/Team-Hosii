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
	size_t frame_count;
	size_t interval;
	size_t read_num;
	COLORREF old_color;
public:
	EventMsg(const std::string &_filename, const size_t _interval = 1, const size_t _read_num = 1, const COLORREF _color = RGB(0, 0, 0))
		: font()
		, is(_filename)
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
		, old_color(RGB(0, 0, 0))
	{
		font.ImageCreate("./data/image/font/myfont.bmp");
		Color(_color);
	}
	EventMsg(const size_t _interval = 1, const size_t _read_num = 1, const COLORREF _color = RGB(0, 0, 0))
		: font()
		, is()
		, frame_count(0)
		, interval(_interval)
		, read_num(_read_num)
		, old_color(RGB(0, 0, 0))
	{
		font.ImageCreate("./data/image/font/myfont.bmp");
		Color(_color);
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
	const size_t Interval(const size_t _interval)
	{
		const size_t old = interval;
		interval = _interval;
		return old;
	}
	const size_t ReadNum(const size_t _read_num)
	{
		const size_t old = read_num;
		read_num = _read_num;
		return old;
	}
	const bool Color(const COLORREF _color)
	{
		if (_color == old_color) return 0;
		auto _image = font.GetImageHandle();
		if (!_image) return 0;
		auto _width = font.GetBmpInfo().bmWidth;
		auto _height = font.GetBmpInfo().bmHeight;
		for (LONG y = 0; y < _height; ++y)
		{
			for (LONG x = 0; x < _width; ++x)
			{
				const COLORREF _p_color = GetPixel(_image, x, y);
				if (_p_color != old_color) continue;
				SetPixel(_image, x, y, _color);
			}
		}
		old_color = _color;
		return 1;
	}
	const Result Run()
	{
		++frame_count;
		if (frame_count >= interval)
		{
			frame_count = 0;
			if (is.Eof()) return Result::RES_EOF;
			std::string _in;
			is.Read(_in, read_num);
			/*アスキーコード読み込みなら*/
			if (_in.length() == 1)
			{
				auto CmdComp = [&_in](const char _r)
				{
					return _in.at(0) == _r;
				};
				if (CmdComp('['))
				{
					std::string _interval_string;
					is.Get(_interval_string, ',');
					interval = atoi(_interval_string.c_str());
					std::string _color_val;
					is.Get(_color_val, ']');
					if (_color_val == "default") return Result::RES_SUCCESS;
					/*初めのカンマまで*/
					auto _first = _color_val.find(',');
					auto _r = _color_val.substr(0, _first);
					auto _second = _color_val.find(',', _first + 1);
					auto _g = _color_val.substr(_first + 1, _second - _first - 1);
					auto _b = _color_val.substr(_second + 1);
					Color(RGB(atoi(_r.c_str()), atoi(_g.c_str()), atoi(_b.c_str())));
					return Result::RES_SUCCESS;
				}
				//if (CmdComp('#'))
				//{
				//	std::string _color;
				//	BYTE _rgb[3];
				//	for (auto &c : _rgb)
				//	{
				//		is.Get(_color, ',');
				//		c = atoi(_color.c_str());
				//	}
				//	Color(RGB(_rgb[0], _rgb[1], _rgb[2]));
				//	return Result::RES_SUCCESS;
				//}
			}
			msg += _in;
		}
		return Result::RES_SUCCESS;
	}
	void DrawAscii(const Point &_pos, const float _width, const float _height)
	{
		Frec _src(0.f, 0.f, 6.f, 24.f);
		draw.Scaling(_width, _height);
		for (size_t i = 0; i < msg.size(); ++i)
		{
			Point _d_pos = _pos;
			_d_pos.x += i * (_width + 2);
			draw.SetPos(&_d_pos);
			_src.l = (msg.at(i) % 32) * 6.f;
			_src.t = (msg.at(i) / 32) * 24.f;
			draw.Draw(&font, &_src, false);
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