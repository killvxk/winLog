//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include "eventLog.h"
#include "logService.hpp"
#include <ComDef.h>
#include <iostream>

namespace wls
{
	static std::string _get_app_path()
	{
		char path[MAX_PATH + 1];
		::GetModuleFileName(nullptr, path, sizeof(path) / sizeof(path[0]));
		return std::string(path);
	}

	static std::string _get_last_error_string(DWORD errorCode)
	{
		if (errorCode)
		{
			HRESULT hr = __HRESULT_FROM_WIN32(errorCode);
			_com_error err(hr);
			return err.ErrorMessage();
		}

		return std::string();
	}

	static void _report_last_error(std::string const& message)
	{
		DWORD errorCode = ::GetLastError();
		if (errorCode)
		{
			OutputDebugString(message.c_str());
			OutputDebugString(_get_last_error_string(errorCode).c_str());
			OutputDebugString("\n");
		}
	}
	
	Service::Service(std::string const& appName) : _appName(appName)
	{
		_keyPath = "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\" + appName;

		auto err = ::RegCreateKeyEx(HKEY_LOCAL_MACHINE, _keyPath.c_str(), 0, 0, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, 0, &_key, 0);
		if (ERROR_SUCCESS == err)
		{
			auto const appPath = _get_app_path();
			err = RegSetValueEx(_key, "EventMessageFile", 0, REG_SZ, reinterpret_cast<BYTE const*>(appPath.c_str()), static_cast<DWORD>(appPath.length()));

			if (ERROR_SUCCESS == err)
			{
				DWORD const typesSupported = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;
				err = ::RegSetValueEx(_key, "TypesSupported", 0, REG_DWORD, reinterpret_cast<BYTE const*>(&typesSupported), sizeof(typesSupported));

				if (ERROR_SUCCESS != err)
					_report_last_error("Failed to install source: ");
				
				::RegCloseKey(_key);
			}
		}
		else
			_report_last_error("Failed to install source: ");
	}

	Service::~Service()
	{
		DWORD err = ::RegDeleteKey(HKEY_LOCAL_MACHINE, _keyPath.c_str());
		if (ERROR_SUCCESS != err)
			_report_last_error("Failed to install source: ");
	}

	void Service::logInformation(std::string message)
	{
		_log(message, EVENTLOG_INFORMATION_TYPE, MSG_INFO_1);
	}

	void Service::logWarning(std::string message)
	{
		_log(message, EVENTLOG_WARNING_TYPE, MSG_WARNING_1);
	}

	void Service::logError(std::string message)
	{
		_log(message, EVENTLOG_ERROR_TYPE, MSG_ERROR_1);
	}

	void Service::_log(std::string const& message, WORD type, DWORD eventID)
	{
		HANDLE hEventLog = ::RegisterEventSource(nullptr, _appName.c_str());

		if (hEventLog)
		{
			auto text = message.c_str();
			if (FALSE == ::ReportEvent(hEventLog, type, 0, eventID, nullptr, 1, 0, &text, 0))
				_report_last_error("Failed to write message: ");

			::DeregisterEventSource(hEventLog);
		}
		else
			_report_last_error("Failed to open source");
	}
} // namespace wls