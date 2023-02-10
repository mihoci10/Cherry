#pragma once

namespace Cherry {

	enum class RendererPlatform {
		None = 0, OpenGL = 1, Vulkan = 2
	};

	class RendererSettings {
	public:
		RendererSettings() = delete;
		RendererSettings(RendererPlatform platform, bool debugMode) : platform(platform), debugMode(debugMode) {}

		const RendererPlatform platform = RendererPlatform::None;
		const bool debugMode = false;

		std::function<void(
			uint8_t severity, 
			std::string_view description, 
			std::string_view source)>
			logCallback = nullptr;
	};

}