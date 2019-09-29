
//MACROS

#pragma once

#include <memory>


#ifdef HZ_PLATFORM_WINDOWS											//export active for DLL, import active for a client app
	#if HZ_DYNAMIC_LINK												//HZ abbr. for macros
		#ifdef HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)					//*
		#else
			#define HAZEL_API __declspec(dllimport)					//**
		#endif
	#else
		#define HAZEL_API
	#endif
#else
	#error Hazel only supports Windows!
#endif


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



#define BIT(x) (1 << x)												//associate an event with an event category




//dispatch
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}




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