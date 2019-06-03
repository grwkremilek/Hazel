
//WINDOW SETUP, IMGUI CONTEXT SETUP, APPLICATION RUNNING

#include "hzpch.h"									//include a collection of standard library header files
#include <glad/glad.h>								//OpenGL Loading Library; loads pointers to OpenGL functions

#include "Application.h"
#include "Input.h"									//class checking the keys and mouse

#include "Hazel/Log.h"								//logging system for the engine and apps					


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)//??*

	Application* Application::s_Instance = nullptr;								//*

	Application::Application()													//constructor
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");				//log
		s_Instance = this;														//*

		m_Window = std::unique_ptr<Window>(Window::Create());					//create a window
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));						//*

		m_ImGuiLayer = new ImGuiLayer();										//memory allocation on the heap
		PushOverlay(m_ImGuiLayer);												//push a layer at the end of the layerstack		

		//VERTICES
		glGenVertexArrays(1, &m_VertexArray);							//generate a vertex array object name
		glBindVertexArray(m_VertexArray);								//bind the vertex array object with a name

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));	//create a new data store for a buffer object

		glEnableVertexAttribArray(0);												//enable a generic vertex attribute array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);//define an array of vertex attribute data
		
		//INDICES
		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


		//SHADERS
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));							//??
	}


	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);										//push a layer at the end of the layerstack
		layer->OnAttach();
	}


	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);									//push an overlayer at the end of the layerstack
		layer->OnAttach();													//??
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);										//define a dispatcher
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));//??

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )	//iterate layerstack from the end
		{
			(*--it)->OnEvent(e);											//??
			if (e.Handled)							//when the event handled in a layer, break
				break;
		}
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);			//specify clear values for the color buffers
			glClear(GL_COLOR_BUFFER_BIT);				//clear buffers to preset values

			m_Shader->Bind();							//bind a shader
			glBindVertexArray(m_VertexArray);			//bind a vertex array object
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);	//render primitives from array data

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)			//iterate the layerstack and render layers
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();						//poll events and swap buffers
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}



/*
bind()


nullptr
- meant as a replacement to NULL
- provides a typesafe pointer value representing an empty (null) pointer

this
holds the address of current object

-> (arrow)
 access to a member function/variable of an object through a pointer
 a->b means (*a).b


*/