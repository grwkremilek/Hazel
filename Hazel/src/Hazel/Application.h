#pragma once

//WINDOW SETUP, IMGUI CONTEXT SETUP, APPLICATION RUNNING

#include "Core.h"								//include macros
#include "Window.h"								//create a window instance

#include "Hazel/LayerStack.h"					//create layerstack to push and pop layers
#include "Hazel/Events/Event.h"					//includes event class
#include "Hazel/Events/ApplicationEvent.h"		//events connected to the window, rendering
#include "Hazel/ImGui/ImGuiLayer.h"				//creates an ImGui control context
#include "Hazel/Renderer/Shader.h"				//bind-unbind shaders
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {

	class HAZEL_API Application								//HAZEL_API macro for __dllexport
	{
	public:													//methods related to the window*
		Application();										//declaration
		virtual ~Application();								//virtual destructor*
		
		void Run();											//method controlling the shaders, renderer, layers
		void OnEvent(Event& e);								//dispatch an event to other layers*
		
		bool m_Running = true;								//control the running of an application
		bool OnWindowClose(WindowCloseEvent& e);			//change m_Running to false

		std::unique_ptr<Window> m_Window;					//create a member window*
		
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		void PushLayer(Layer* layer);						//*
		void PushOverlay(Layer* layer);

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		static Application* s_Instance;								//??


		inline Window& GetWindow() { return *m_Window; }			//returns the size of the window
		inline static Application& Get() { return *s_Instance; }	//??*
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}


/*
public
accessible by all who have acess to the class Application
private
only accessible from within the class


virtual destructors
 prevent deletion of an instance of a derived class through a pointer to the base class

 unique pointers
 own and manage another object through a pointer and dispose of that object when the unique_ptr goes out of scope


 & = reference to (another variable)
 *= pointer (stores an address)

 static
 accessible only from other functions in the same file
*/