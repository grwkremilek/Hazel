#pragma once

//GENERAL STRUCTURE FOR A WINDOW

#include "hzpch.h"				//include a collection of standard library header files

#include "Hazel/Core.h"			//include macros
#include "Hazel/Events/Event.h"	//include general class for an event

namespace Hazel {

	struct WindowProps			//window properties*
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;		//EventCallbackFn as alias for std::function...*

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;					//*
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;					//vertical synchronization
		virtual bool IsVSync() const = 0;							//get info about vertical synchronization

		virtual void* GetNativeWindow() const = 0;					//  

		static Window* Create(const WindowProps& props = WindowProps());
	};
}

/*
structure vs class
- structs have default public members and bases and classes have default private members and bases
- both classes and structs can have a mixture of public, protected and private members, can use inheritance and can have member functions

using
= alias

std::function
 - general-purpose polymorphic function wrapper
 - will take any function with given parameters (in this case void and Event as parameter)


pure virtual functions
= a virtual function that is required to be implemented by a derived class if the derived class is not abstract

*/
