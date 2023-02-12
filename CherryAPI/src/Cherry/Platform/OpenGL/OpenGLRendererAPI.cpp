#include "OpenGLRendererAPI.h"

#include <Cherry/Utils/Log.hpp>

#include <GL/glew.h>
#include <SDL.h>

void GLAPIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
							GLsizei length, const GLchar* message, const void* userParam);

namespace Cherry {

	void OpenGLRendererAPI::Init()
	{
		GLenum res;

		m_ctx = SDL_GL_CreateContext(RendererAPI::GetWindowHnd().get());
		res = glewInit();

		if (RendererAPI::GetSettings()->debugMode) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, this);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::Deinit()
	{
		SDL_GL_DeleteContext(m_ctx);
		RendererAPI::Deinit();
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void GLAPIENTRY OpenGLMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	Cherry::OpenGLRendererAPI* renderer = (Cherry::OpenGLRendererAPI*) userParam;

	CHERRY_DISPATCH_LOG_LOC(severity, std::string_view(message, length), Cherry::StringFormatter::format("(src: %d type: %d id: %d)", source, type, id));
}