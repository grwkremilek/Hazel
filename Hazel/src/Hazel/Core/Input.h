#pragma once

//MOUSE AND KEYBOARD INPUT POLLING MANAGER

#include "Hazel/Core/Core.h"

namespace Hazel {

	class HAZEL_API Input
	{
	protected:
		Input() = default;						//https://github.com/TheCherno/Hazel/issues/97

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }		//static IsKezPressed calls a per platform implementation

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	
	protected:																//*
		virtual bool IsKeyPressedImpl(int keycode) = 0;						//implemented for each platform separately

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	
	private:
		static Input* s_Instance;											//globally only one window manager (even if more windows)
	};
}

/*
protected
accessible from derived classes

*/
