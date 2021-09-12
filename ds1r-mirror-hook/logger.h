#pragma once

#include <fstream>
#include <sstream>
#include <mutex>
#include <memory>

enum class LogEndl { INFO, ERRO, WARN, ENDL };

class Logger
{
private:
	class SyncLogger
	{
	public:
		SyncLogger();
		~SyncLogger();
		void log(std::string str);
		std::ofstream logOut;
		std::mutex mutex;
	};
	SyncLogger& sync;

public:
	static Logger getInstance();

	static bool enabled;

	template <typename T>
	Logger& operator<< (const T& x)
	{
		sstream << x;
		return *this;
	}
	Logger& operator<< (LogEndl s);

private:
	Logger(Logger::SyncLogger& sync) : sync(sync) {}
	std::stringstream sstream;
	std::stringstream prefixSstream;
};

void MyDebugBreak();

#define LOG if (!Logger::enabled) {} else Logger::getInstance()

#define CHECK(expr) \
	do { \
		long __hr = (long)(expr); \
		if (__hr != 0) \
			LOG << "(" << __FILE__ << ":" << ##__LINE__ << ") Expression returned " << std::hex << __hr << ": " << #expr << LogEndl::ERRO; \
	} while (0)

#define CHECK_TRUE(expr) \
	do { \
		bool __hr = (bool)(expr); \
		if (__hr != true) \
			LOG << "(" << __FILE__ << ":" << ##__LINE__ << ") Expression returned false: " << #expr << LogEndl::ERRO; \
	} while (0)