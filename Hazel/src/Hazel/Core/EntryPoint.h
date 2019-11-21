
//choice of GPU
//logging system initialization
//MAIN function for WINDOWS

#pragma once

#include "Hazel/Core/Core.h"

#ifdef HZ_PLATFORM_WINDOWS

//extern Hazel::Application* Hazel::CreateApplication();

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }		// choose Nvidia card


int main(int argc, char** argv)													//**
{
	Hazel::Log::Init();

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}
#endif



/*

*
extern
using extern int x; tells the compiler that an object of type int called x exists somewhere


**
int main(int argc, char** argv)
- int: function returns 0 or 1 (succeed x fail)
- int argc: number of strings pointed to by argv (argument count)
- char** argv: the array of arguments (argument vector) 
*/