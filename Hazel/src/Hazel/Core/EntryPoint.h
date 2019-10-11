
//choice of GPU
//logging system initialization
//MAIN function for WINDOWS

#pragma once

#ifdef HZ_PLATFORM_WINDOWS

//extern Hazel::Application* Hazel::CreateApplication();

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }		// choose Nvidia card


int main(int argc, char** argv)													//**
{
	Hazel::Log::Init();															//initiate logging system
	HZ_CORE_WARN("Initialized Log!");
	std::string a = "The logging system has been initalized.";
	HZ_INFO("Hello!", a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
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