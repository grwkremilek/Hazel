#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();		//allows not to specify which application is being called

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello! Var={0}", a);

	auto app = Hazel::CreateApplication();					//initialize an app (new allocates heap memory)
	app->Run();
	delete app;												//deallocate memory from heap
}

#endif