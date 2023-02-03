#pragma once

#include <Cherry/RenderContext.h>

namespace Cherry {

	class OpenGLContext : public RenderContext {

	public:
		OpenGLContext(std::shared_ptr<SDL_Window> windowHandle) : RenderContext(windowHandle) {}

		virtual void Init();
	};

}