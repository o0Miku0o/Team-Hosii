#pragma once

#include <Windows.h>
#include <Shlwapi.h>
#include <fstream>
#include <string>
#include <vector>

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Shlwapi.lib")

class MciScript
{
public:
	enum Result
	{
		MS_FAILURE,
		MS_FILE_NOT_OPENED,
		MS_NOT_ALLOC_BUFFER,
		MS_SEND_ERROR,
		MS_EMPTY,
		MS_SUCCESS,
		MS_COMPLETE,
	};
private:
	std::vector<std::string> mci_script;
	static void _error_to_message(const MCIERROR _err)
	{
		char _buff[1024] = {};
		mciGetErrorString(_err, _buff, sizeof(_buff) / sizeof(_buff[0]));
		MessageBox(nullptr, _buff, "mci error", MB_OK | MB_ICONWARNING);
	}
public:
	MciScript()
		: mci_script()
	{

	}
	const Result Read(const std::string &_mci_script_filename)
	{
		std::ifstream ifs(_mci_script_filename);
		if(!ifs)return Result::MS_FILE_NOT_OPENED;
		char _buff[1024] = {};
		while (!ifs.eof())
		{
			ifs.getline(_buff, sizeof(_buff));
			mci_script.emplace_back(_buff);
		}
		ifs.close();
		return Result::MS_SUCCESS;
	}
	void Clear()
	{
		mci_script.clear();
	}
	const Result Send()
	{
		if (Nothing()) return Result::MS_EMPTY;
		char _ret_buff[1024] = {};
		const MCIERROR _result = mciSendString(mci_script.at(0).c_str(), _ret_buff, sizeof(_ret_buff), nullptr);
		if (_result)
		{
			_error_to_message(_result);
			return Result::MS_SEND_ERROR;
		}
		mci_script.erase(mci_script.begin());
		return (Nothing()) ? Result::MS_COMPLETE : Result::MS_SUCCESS;
	}
	const bool Nothing() const
	{
		return !mci_script.size();
	}
	const size_t Size() const
	{
		return mci_script.size();
	}
};