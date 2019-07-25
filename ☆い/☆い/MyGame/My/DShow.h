#pragma once

#include <Windows.h>
#include <string>
#include <dshow.h>

#pragma comment (lib, "strmiids.lib")

//#define USE_COM_INTERFACE

enum DShowType
{
	DT_PLAY_VIDEO,
};

template<DShowType>
class DShow;

template<>
class DShow<DShowType::DT_PLAY_VIDEO>
{
private:
	HRESULT result;
	IGraphBuilder *graph_builder;
	IMediaControl *media_control;
	IMediaEvent *media_event;
	IVideoWindow *video_window;
public:
	DShow(const HWND _owner, const std::string &_filename)
	{
		result = CoCreateInstance
		(
			CLSID_FilterGraph, nullptr,
			CLSCTX_INPROC,
			IID_IGraphBuilder,
			(void **)&graph_builder
		);
		if (FAILED(result)) return;
		result = graph_builder->QueryInterface(IID_IMediaControl, (void **)&media_control);
		if (FAILED(result))
		{
			graph_builder->Release();
			return;
		}
		result = graph_builder->QueryInterface(IID_IMediaEvent, (void **)&media_event);
		if (FAILED(result))
		{
			graph_builder->Release();
			media_control->Release();
			return;
		}
		//unicode
		result = media_control->RenderFile((BSTR)_filename.c_str());
		if (FAILED(result))
		{
			graph_builder->Release();
			media_control->Release();
			media_event->Release();
			return;
		}
		result = graph_builder->QueryInterface(IID_IVideoWindow, (void **)&video_window);
		if (FAILED(result))
		{
			graph_builder->Release();
			media_control->Release();
			media_event->Release();
			return;
		}
		result = video_window->put_Owner((OAHWND)_owner);
		if (FAILED(result))
		{
			graph_builder->Release();
			media_control->Release();
			media_event->Release();
			video_window->Release();
			return;
		}
		result = video_window->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
		if (FAILED(result))
		{
			graph_builder->Release();
			media_control->Release();
			media_event->Release();
			video_window->Release();
			return;
		}
		RECT _client = {};
		GetClientRect(_owner, &_client);

		video_window->SetWindowPosition(_client.left, _client.top, _client.right - _client.left, _client.bottom - _client.top);
		video_window->SetWindowForeground(OATRUE);
		video_window->put_Visible(OATRUE);
		media_control->Run();
		media_event->WaitForCompletion(-1, nullptr);

		graph_builder->Release();
		media_control->Release();
		media_event->Release();
		video_window->Release();
	}
	virtual ~DShow()
	{

	}
};