//macros

#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif



/*
__declspec(dllexport)
A DLL file has a layout very similar to an .exe file, with one important difference — a DLL file contains an exports table. The exports table contains the name of every function that the DLL exports to other executables. These functions are the entry points into the DLL; only the functions in the exports table can be accessed by other executables. __declspec(dllexport) allows the compiler to generate the export names automatically and place them in a .lib file. This .lib file can then be used just like a static .lib to link with a DLL.


__declspec(dllimport)
When you create header files for applications that use your DLLs to build with, use __declspec(dllimport) on the declarations of the public symbols. Using __declspec(dllimport) is optional on function declarations, but the compiler produces more efficient code if you use this keyword. However, you must use __declspec(dllimport) for the importing executable to access the DLL's public data symbols and objects.

*/