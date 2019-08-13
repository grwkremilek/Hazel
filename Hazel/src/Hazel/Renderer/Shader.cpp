#include "hzpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	Shader::Shader(const std::string& vertexSrc, const std::string& FragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);						// Create an empty vertex shader handle
		
		const GLchar *source = (const GLchar *)vertexSrc.c_str();					// Send the vertex shader source code to GL
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);												// Compile the vertex shader
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);									// The maxLength includes the NULL character
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex shader compilation error!");
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);					// Create an empty fragment shader handle

		source = (const GLchar *)FragmentSrc.c_str();								// Send the fragment shader source code to GL
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);											// Compile the fragment shader
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);									// The maxLength includes the NULL character
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment shader compilation error!");
			return;
		}

																					// Vertex and fragment shaders are successfully compiled.
																					// Now time to link them together into a program.
		m_RendererID = glCreateProgram();											// Get a program object.
		glAttachShader(m_RendererID, vertexShader);									// Attach our shaders to our program
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);												// Link our program

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);									// The maxLength includes the NULL character
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);											// We don't need the program anymore.
			glDeleteShader(vertexShader);											// Don't leak shaders either.
			glDeleteShader(fragmentShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure !");
			return;
		}

		glDetachShader(m_RendererID, vertexShader);									// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}
}