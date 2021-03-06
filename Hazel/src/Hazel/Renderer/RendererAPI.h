#pragma once

//RENDERER IMPLEMENTATION PER PLATFORM (OpenGL, ...Vulcan, DirectX, Metal...)
//each platform will contain classes: render context, swap chain, framebuffer, vertex buffer, index buffer, texture, shader, states, pipelines, render passes

#include <glm/glm.hpp>
#include "Hazel/Renderer/VertexArray.h"


namespace Hazel {

	class RendererAPI {
	public:
		enum class API					
		{
			None = 0, OpenGL = 1
		};
	public:															//interface for different platforms
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; };
		static Scope<RendererAPI> Create();

	private:
		static API s_API;			//what API is active
	};

}
