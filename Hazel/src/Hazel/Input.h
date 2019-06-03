#pragma once

//MOUSE AND KEYBOARD INPUT

#include "Hazel/Core.h"									//include macros

namespace Hazel {

	class HAZEL_API Input								//HAZEL_API macro for __dllexport
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }					//keys

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }	//mouse
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	
	protected:																//*
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;				//defined for each platform semarately
		virtual std::pair<float, float> GetMousePositionImpl() = 0;			//WindowsInput.cpp
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	
	private:
		static Input* s_Instance;											//??
	};
}

/*
protected
accessible from derived classes

*/
