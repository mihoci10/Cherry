#pragma once

#include <Cherry/RendererAPI.h>

namespace Cherry {

	class OpenGLRendererAPI: public RendererAPI {
	public:
		OpenGLRendererAPI() : RendererAPI() {};

		virtual void Init() override;
		virtual void Deinit() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

	private:
		SDL_GLContext m_ctx;
	};

}