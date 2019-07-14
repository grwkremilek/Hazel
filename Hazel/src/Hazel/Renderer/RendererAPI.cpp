//RENDERER IMPLEMENTATION PER PLATFORM

#include "hzpch.h"
#include "RendererAPI.h"


namespace Hazel {
	 
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;					//will contain a switch statement
}