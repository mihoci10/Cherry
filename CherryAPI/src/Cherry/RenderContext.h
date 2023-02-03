#pragma once

#include <SDL3/SDL.h>

namespace Cherry {

	class RenderContext {

	public:
		RenderContext() = delete;
		virtual ~RenderContext() = default;

		static std::shared_ptr<RenderContext> Create(std::shared_ptr<SDL_Window> windowHandle);

		virtual void Init() = 0;

	protected:
		RenderContext(std::shared_ptr<SDL_Window> windowHandle) : m_WndHnd(windowHandle) {}
		std::shared_ptr<SDL_Window> m_WndHnd;
	};

}