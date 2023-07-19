#include "OpenGLRendererAPI.h"

#include <Cherry/Utils/Log.hpp>

#include <GL/glew.h>
#include <SDL.h>

void GLAPIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
							GLsizei length, const GLchar* message, const void* userParam);

namespace Cherry {

	OpenGLRendererAPI::OpenGLRendererAPI(std::shared_ptr<SDL_Window> windowHandle,
		RendererSettings rendererSettings)
		: RendererAPI(windowHandle, rendererSettings)
	{
		GLenum res;
		const char* errMsg;

		SDL_ClearError();
		m_ctx = SDL_GL_CreateContext(m_WindowHandle.get());
		if (m_ctx == NULL) {
			errMsg = SDL_GetError();
			CHERRY_THROW("SDL could not acquire OpenGL context! (Reason: %s)", errMsg);
			return;
		}

		res = glewInit();
		if (res != GLEW_OK) {
			errMsg = (const char*)glewGetErrorString(res);
			CHERRY_THROW("GLEW could not be initialized! (Reason: %s)", errMsg);
		}

		if (m_RendererSettings.debugMode) {
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

	OpenGLRendererAPI::~OpenGLRendererAPI() const
	{
		SDL_GL_DeleteContext(m_ctx);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawTriangles(VertexBuffer& vertexBuffer) const
	{
		vertexBuffer.Bind();
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexBuffer.GetCount()));
		vertexBuffer.Unbind();
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
	
	CHERRY_DISPATCH_LOG_LOC(renderer, severity, std::string_view(message, length), Cherry::StringFormatter::format("(src: %d type: %d id: %d)", source, type, id));
}