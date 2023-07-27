#include "BufferBatch.h"

#include <Cherry/Utils/Log.hpp>
#include <Cherry/Platform/OpenGL/OpenGLBufferBatch.h>

namespace Cherry{

	std::unique_ptr<BufferBatch> BufferBatch::Create(const RendererSettings& rendererSettings)
	{
        switch (rendererSettings.platform)
        {
        case RendererPlatform::None:
            CHERRY_THROW("Buffer Batch is not supported in headless mode!");
        case RendererPlatform::OpenGL:
            return std::make_unique<OpenGLBufferBatch>();
        case RendererPlatform::Vulkan:
            CHERRY_THROW("Buffer Batch is not supported in for Vulkan!");
        }
        CHERRY_THROW("Unsupported render platform encountered!");
	}
}