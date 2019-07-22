#include <Hazel.h>

#include "imgui/imgui.h"


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Cube"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(Hazel::VertexArray::Create());		//switch to an opengl array


		float vertices[24 * 7] = {
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,		//front
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,		//right
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//back
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//left
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,		//upper
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//bottom
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;		//create a vertex buffer
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices))); // switch to opengl and create buffer

		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[36] = { 0, 1, 2, 0, 2, 3,			//front
								4, 5, 6, 4, 6, 7,			//right
								8, 9, 10, 8, 10, 11,		//back 
								12, 13, 14, 12, 14, 15,		//left
								16, 17, 18, 16, 18, 19,		//upper
								20, 21, 22, 20, 22, 23		//bottom
		};
		std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));

	}



	void OnUpdate(Hazel::Timestep ts) override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}



		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();
	}




	virtual void OnImGuiRender() override
	{
	}


	void OnEvent(Hazel::Event& event) override
	{
	}

private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;

	std::shared_ptr<Hazel::Shader> m_BlueShader;
	std::shared_ptr<Hazel::VertexArray> m_SquareVA;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

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