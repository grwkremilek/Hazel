#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {


	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)	//*bind a window event with the window 

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());							//*create a window object
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));								//*call a SetEventCallback function on the window
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	//bind an event with an event dispatcher
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);													//declare a dispatcher
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));			//close a window

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )				//iterate the stack backwards
		{
			(*--it)->OnEvent(e);														//handle events
			if (e.Handled)																//if a new event, break
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.6, 0.6, 0, 1);												//specify clear values for the color buffers
			glClear(GL_COLOR_BUFFER_BIT);												//clear buffers to preset value

			for (Layer* layer : m_LayerStack)											//iterate the stack and update layers
				layer->OnUpdate();

			m_Window->OnUpdate();		 												//proces queued window events
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

/*
std::bind() = binds arguments to a function
 std::placeholders::_1 = argument will be speciafied by the user

 std::unique_ptr = a smart pointer that manages another object and disposes of that object when the unique_ptr goes out of scope
 -> = arrow operator used for a pointer, because a pointer cannot call a function, ie dereferences a pointer, (*pointer) == pointer->
*/