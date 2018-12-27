//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include "eventLog.h"
#include "logService.hpp"
#include <ComDef.h>

namespace wls
{
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

	static void _report_error(std::string const& message, DWORD errorCode)
	{
		if (errorCode)
		{
			OutputDebugString(message.c_str());
			OutputDebugString(_get_last_error_string(errorCode).c_str());
			OutputDebugString("\n");
		}
	}

	Service::Service(std::string const& appName) : _appName(appName)
	{
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
				_report_error("Failed to write message: ", ::GetLastError());

			::DeregisterEventSource(hEventLog);
		}
		else
			_report_error("Failed to open source.", ::GetLastError());
	}
} // namespace wls