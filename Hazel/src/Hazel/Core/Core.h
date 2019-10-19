#pragma once

//MACROS

#include <memory>


// PLATFORM DETECTION
#ifdef _WIN32										// Windows x64/x86 
	#ifdef _WIN64
		#define HZ_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif

#elif defined(__APPLE__) || defined(__MACH__)		//MAC Apple
	#include <TargetConditionals.h>				
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define HZ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

#elif defined(__ANDROID__)						//Linux
	#define HZ_PLATFORM_ANDROID					//Android based on linux, must be checked before __linux__
	#error "Android is not supported!"
#elif defined(__linux__)
	#define HZ_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif


// DLL support
#ifdef HZ_PLATFORM_WINDOWS
	#if HZ_DYNAMIC_LINK
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#define HAZEL_API
	#endif
#else
	#error Hazel only supports Windows!
#endif // End of DLL support


//check a condition and if it fails, break at the failing line of code
#ifdef HZ_DEBUG
#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif


//associate an event with an event category
#define BIT(x) (1 << x)



//dispatch
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}


//Prokopova template
template <typename T> 
void new_(T*& t) { t = new T(); };


/*

*
__declspec(dllexport)
 - DLL file similar in layout to an .exe file + contains an exports table
 - exports table contains the name of every function that the DLL exports to other executables
 - these functions are the entry points into the DLL; only the functions in the exports table can be accessed by other executables
 -__declspec(dllexport) allows the compiler to generate the export names automatically and place them in a .lib file
 - this .lib file can then be used just like a static .lib to link with a DLL


 **
__declspec(dllimport)
- use in the header files for applications using the DLL
- using __declspec(dllimport) is optional on function declarations, but the compiler produces more efficient code if you use this keyword
- must use __declspec(dllimport) for the importing executable to access the DLL's public data symbols and objects
*/