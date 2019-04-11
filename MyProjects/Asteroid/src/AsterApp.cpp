#include <Hazel.h>

class Asteroid : public Hazel::Application
{
public:
	Asteroid()
	{

	}

	~Asteroid()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Asteroid();
}