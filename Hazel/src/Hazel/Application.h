//controls life cycle of the application as well as events (mouse, keyboard etc.)
//contains run loop

#pragma once

#include "Core.h"
#include "Window.h"

#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// to be defined in CLIENT
	Application* CreateApplication();

}

/*
virtual destructor
If your derived class destructor is virtual then objects will be destrcuted in a order(firstly derived object then base ). If your derived class destructor is NOT virtual then only base class object will get deleted(because pointer is of base class "Base *myObj"). So there will be memor leak for derived object. (The class Application will be sublassed by individual apps.)
*/