//RENDERER IMPLEMENTATION PER PLATFORM (OpenGL, ...Vulcan, DirectX, Metal...)
//each platform will contain classes: render context, swap chain, framebuffer, vertex buffer, index buffer, texture, shader, states, pipelines, render passes

#include "hzpch.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace Hazel {
	 
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;					//will contain a switch statement
	
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}