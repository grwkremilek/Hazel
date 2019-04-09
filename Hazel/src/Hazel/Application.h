#pragma once

#include "Events/Event.h"
#include "Core.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();				//virtual destructor bc the class will be subclassed

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


