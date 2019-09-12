//RENDERER IMPLEMENTATION PER PLATFORM (OpenGL, ...Vulcan, DirectX, Metal...)

#include "hzpch.h"
#include "RendererAPI.h"


namespace Hazel {
	 
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;					//will contain a switch statement
}