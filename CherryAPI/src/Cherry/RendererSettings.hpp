#pragma once

namespace Cherry {

	enum class RendererPlatform {
		None = 0, OpenGL = 1, Vulkan = 2
	};

	class RendererSettings {
	public:
		const RendererPlatform platform = RendererPlatform::None;
	};

}