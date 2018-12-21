//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include <string>

#include "win32api.hpp"

namespace wls
{
	/// Client to log via the Windows Event Log.
	class Service
	{
	public:
		/// Constructor.
		Service(std::string const& appName);

		/// Destructor.
		~Service();

		void logInformation(std::string message);
		void logWarning(std::string message);
		void logError(std::string message);
	
	private:
		void _log(std::string const& message, WORD type, DWORD eventID);
	
	private:
		std::string const _appName;
		std::string _keyPath;
		HKEY _key{ nullptr };
	};
} // namespace wls
