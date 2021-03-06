
//WINDOW SETUP, 
//IMGUI CONTEXT SETUP
//APPLICATION LIFE CYCLE

#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Window.h"

#include "Hazel/Core/LayerStack.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/OrthographicCamera.h"


namespace Hazel {

	class Application
	{
	public:																	//*														
		Application();
		virtual ~Application();
																		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;									//***
		ImGuiLayer* m_ImGuiLayer;
		
		bool m_Running = true;
		bool m_Minimized = false;
		
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;										//****
	};

	// To be defined in a client app
	Application* CreateApplication();

}


/*

*
public
accessible by all who have acess to the class Application
private
only accessible from within the class


**
virtual destructors
 prevent deletion of an instance of a derived class through a pointer to the base class

 ***
 unique pointers
 own and manage another object through a pointer and dispose of that object when the unique_ptr goes out of scope


 ****
 static
 accessible only from other functions in the same file
*/