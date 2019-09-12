
//LOGGING SYSTEM (for the engine and its client apps)


#include "hzpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;			//*
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");					//timestamp + type(core/client) + message
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

/*

*
shared pointers
-a stack-allocated object that wraps a pointer so that you don't have to know who owns it
- when the last shared pointer for an object in memory is destructed, the wrapped pointer will also be deleted


*/