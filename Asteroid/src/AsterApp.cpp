#include <Hazel.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		static bool show = true;
		ImGui::ShowMainImguiWindow(&show);
	}

	void OnEvent(Hazel::Event& event) override
	{
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Tab key is pressed (event)!");
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Asteroid : public Hazel::Application
{
public:
	Asteroid()
	{
		PushLayer(new ExampleLayer());
	}

	~Asteroid()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Asteroid();
}