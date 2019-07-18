#pragma once

#ifdef _DEBUG
#include <stdio.h>
#include <Windows.h>
#include <crtdbg.h>
#include <string>

inline void MsgBox(const std::string &asText)
{
	MessageBox(nullptr, asText.c_str(), nullptr, MB_OK);
}

class Debug
{
private:
public:
	class Console
	{
	private:
		FILE *fpFile;
		bool bResult;
	public:
		Console()
		{
			bResult = AllocConsole();
			if (!bResult) return;
			freopen_s(&fpFile, "CONOUT$", "w", stdout);
			bResult = fpFile;
			if (!bResult)
			{
				FreeConsole();
			}
		}
		virtual ~Console()
		{
			if (!bResult) return;
			fclose(fpFile);
			FreeConsole();
		}
	};
	static void DetectLeak()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	}
};
#define print printf_s
#else

#define MsgBox(_TEXT_) __noop

class Debug
{
private:
public:
	class Console
	{
	private:
	public:
	};
	static void DetectLeak()
	{

	}
};
#define print __noop
#endif