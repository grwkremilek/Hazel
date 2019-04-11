#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType															//describes event types
	{																				//each event type has an ID assigned
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory							//filters specific type of events, for the needs of logging etc.
	{											//bitfield so that one event able to belong to more categories
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};



	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }




	class HAZEL_API Event												//basic event class
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;						//pure vitrual function
		virtual const char* GetName() const = 0;						//pure vitrual function
		virtual int GetCategoryFlags() const = 0;						//pure vitrual function
		virtual std::string ToString() const { return GetName(); }		//debugging

		inline bool IsInCategory(EventCategory category)				//belongs to a category or not
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;											//used when propagating an event to further layers
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())		//check if an event matches a template
			{
				m_Event.m_Handled = func(*(T*)&m_Event);			//dispatch to an appropriate function
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
