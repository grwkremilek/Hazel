
//LOGGING SYSTEM (for the engine and its client apps)

#pragma once

#include "Hazel/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"																			//fmtlib's ostream support

namespace Hazel {

	class Log
	{
	public:
		static void Init();																				//*

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }		//** spdlog::stdout_color_mt() returns a shared_ptr
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }	//***
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define HZ_CORE_TRACE(...)    ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...)	      ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)	      ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)	      ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)	      ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)	  ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)

/*

*
static function
- all objects of the class share one copy of the static member


**
shared_ptr


***
inline functions
- C++ provides an inline functions to reduce the function call overhead
- expanded in line when it is called. When the inline function is called whole code of the inline function gets inserted or substituted at the point of inline function call
- this substitution is performed by the C++ compiler at compile time

When the program executes the function call instruction the CPU stores the memory address of the instruction following the function call, copies the arguments of the function on the stack and finally transfers control to the specified function. The CPU then executes the function code, stores the function return value in a predefined memory location/register and returns control to the calling function. This can become overhead if the execution time of function is less than the switching time from the caller function to called function (callee). For functions that are large and/or perform complex tasks, the overhead of the function call is usually insignificant compared to the amount of time the function takes to run. However, for small, commonly-used functions, the time needed to make the function call is often a lot more than the time needed to actually execute the functionís code. This overhead occurs for small functions because execution time of small function is less than the switching time.

*/