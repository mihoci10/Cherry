#include "Renderer.h"

#include <Cherry/Utils/Log.hpp>

namespace Cherry {

	std::unique_ptr<RendererAPI> Renderer::s_RendererAPI = nullptr;

	void Renderer::Create(std::shared_ptr<SDL_Window> windowHandle, std::shared_ptr<RendererSettings> rendererSettings)
	{
		s_RendererAPI = RendererAPI::Create(windowHandle, rendererSettings);
	}
}
