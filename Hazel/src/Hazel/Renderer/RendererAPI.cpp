//RENDERER IMPLEMENTATION PER PLATFORM (OpenGL, ...Vulcan, DirectX, Metal...)
//each platform will contain classes: render context, swap chain, framebuffer, vertex buffer, index buffer, texture, shader, states, pipelines, render passes

#include "hzpch.h"
#include "RendererAPI.h"


namespace Hazel {
	 
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;					//will contain a switch statement
}