#pragma once

//IMGUI LAYER RENDERING DEBUG THINGS

#include "Hazel/Core/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;				//sets up ImGui context, style, Platform/Renderer bindings
		virtual void OnDetach() override;				//close a frame, destry context
		virtual void OnImGuiRender() override;			//all ImGui rendering

		void Begin();									//begins a new frame
		void End();
	private:
		float m_Time = 0.0f;
	};

}