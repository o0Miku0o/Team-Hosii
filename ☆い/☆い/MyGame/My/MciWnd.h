#pragma once

#include <Windows.h>
#include <string>
#include <vfw.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"vfw32.lib")

class MciWnd
{
private:
	HWND mci_wnd;
public:
	MciWnd()
		: mci_wnd(nullptr)
	{

	}
	virtual ~MciWnd()
	{
		Close();
	}
	const bool Create(const HWND _parent, const std::string &_filename)
	{
		mci_wnd = MCIWndCreate
		(
			_parent, GetModuleHandle(nullptr),
			WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,
			_filename.c_str()
		);
		return mci_wnd;
	}
	void Close()
	{
		if (!mci_wnd) return;
		MCIWndDestroy(mci_wnd);
	}
	const bool Play()
	{
		if (!mci_wnd) return 0;
		MCIWndPlay(mci_wnd);
		return 1;
	}
};