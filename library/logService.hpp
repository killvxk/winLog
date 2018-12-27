//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include <sstream>
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
		~Service() = default;

		/// Log information message.
		template <typename ...T>
		void logInformation(T&& ...args)
		{
			std::stringstream ss;
			ss << __FILE__ << ":" << __LINE__ << " ";
			using expander = int[];
			(void)expander
			{
				0, (void(ss << std::forward<T>(args) << " "), 0)...
			};
			ss << std::endl;
			logInformation(ss.str());
		}

		/// Log information message.
		void logInformation(std::string message);

		/// Log warning message.
		template <typename ...T>
		void logWarning(T&& ...args)
		{
			std::stringstream ss;
			ss << __FILE__ << ":" << __LINE__ << " ";
			using expander = int[];
			(void)expander
			{
				0, (void(ss << std::forward<T>(args) << " "), 0)...
			};
			ss << std::endl;
			logWarning(ss.str());
		}

		/// Log warning message.
		void logWarning(std::string message);
		
		/// Log error message.
		template <typename ...T>
		void logError(T&& ...args)
		{
			std::stringstream ss;
			ss << __FILE__ << ":" << __LINE__ << " ";
			using expander = int[];
			(void)expander
			{
				0, (void(ss << std::forward<T>(args) << " "), 0)...
			};
			ss << std::endl;
			logError(ss.str());
		}

		/// Log error message.
		void logError(std::string message);
	
	private:
		void _log(std::string const& message, WORD type, DWORD eventID);
	
	private:
		std::string const _appName;
	};
} // namespace wls
