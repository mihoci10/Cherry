#include "RenderContext.h"

#include <Cherry/RendererAPI.h>
#include <Cherry/Platform/OpenGL/OpenGlContext.h>

namespace Cherry {

	std::shared_ptr<RenderContext> RenderContext::Create(std::shared_ptr<SDL_Window> windowHandle)
	{
		switch (RendererAPI::GetSettings()->platform)
		{
			case RendererPlatform::None:
				return nullptr;
			case RendererPlatform::OpenGL:
				return std::make_shared<OpenGLContext>(windowHandle);;
			case RendererPlatform::Vulkan:
				return nullptr;
		}

		return nullptr;
	}

}
