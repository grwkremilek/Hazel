#pragma once

#include "Hazel/Core.h"							//include macros
#include "Hazel/Events/Event.h"					//include genral class for event
#include "Hazel/Core/Timestep.h"

namespace Hazel {

	class HAZEL_API Layer						//macro for __declspec(dllexport)
	{
	public:
		Layer(const std::string& name = "Layer");	//declaration of a layer
		virtual ~Layer();
		virtual void OnAttach() {}					//will be defined where??
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }	//return the name of a layer
	protected:
		std::string m_DebugName;
	};
}