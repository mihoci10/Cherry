#pragma once

#include <Cherry/RendererAPI.h>

namespace Cherry {

	class OpenGLRendererAPI: public RendererAPI {
	public:
		OpenGLRendererAPI(std::shared_ptr<SDL_Window> windowHandle,
			RendererSettings rendererSettings);
		~OpenGLRendererAPI();

		virtual void DrawTriangles(VertexBuffer& vertexBuffer) const override;

		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
		virtual void Clear() const override;

	private:
		SDL_GLContext m_ctx = nullptr;
	};

}