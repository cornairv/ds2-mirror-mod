#include "pch.h"
#include "logger.h"
#include "config.h"
#include <iomanip>

bool Logger::enabled = false;

Logger::SyncLogger::SyncLogger()
{
	if (!config.logFile.empty())
	{
		logOut.open(config.logFile, std::ios_base::app);
		if (logOut.fail())
		{
			std::string errorMsg = "Failed to open file for logging: " + config.logFile;
			MessageBoxA(nullptr, errorMsg.c_str(), "DSMirror Alert", MB_OK);
		}
	}
	if (config.showConsole)
	{
		if (AllocConsole() == 0)
		{
			std::string errorMsg = "Failed to allocate console for logging: " + std::to_string(GetLastError());
			MessageBoxA(nullptr, errorMsg.c_str(), "DSMirror Alert", MB_OK);
		}
	}
}

Logger::SyncLogger::~SyncLogger()
{
	if (logOut.is_open())
	{
		logOut.close();
		FreeConsole();
	}
}

void Logger::SyncLogger::log(std::string str)
{
	std::lock_guard<std::mutex> lock(mutex);
	logOut << str;
	logOut.flush();
	if (config.showConsole)
	{
		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), str.c_str(), static_cast<DWORD>(str.length()), nullptr, nullptr);
	}
}

Logger Logger::getInstance()
{
	static Logger::SyncLogger syncInstance;
	return Logger(syncInstance);
}

Logger& Logger::operator<< (LogEndl s)
{
	time_t now = std::time(nullptr);
	struct tm timebuf;
	localtime_s(&timebuf, &now);
	prefixSstream << std::put_time(&timebuf, "%F %T ");

	switch (s)
	{
	case LogEndl::INFO:
		prefixSstream << "[INFO] ";
		break;
	case LogEndl::ERRO:
		MessageBoxA(nullptr, sstream.str().c_str(), "DSMirror Error", MB_OK);
		prefixSstream << "[ERRO] ";
		break;
	case LogEndl::WARN:
		prefixSstream << "[WARN] ";
		break;
	case LogEndl::ENDL:
		break;
	}
	prefixSstream << sstream.str() << "\n";
	sync.log(prefixSstream.str());
	return *this;
}

void __declspec(noinline) MyDebugBreak()
{
	LOG << "debug" << LogEndl::ENDL;
}
