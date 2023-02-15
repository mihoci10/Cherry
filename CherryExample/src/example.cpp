#include <GL/glew.h>
#include <SDL.h>
#include <Cherry/RendererAPI.h>
#include <Cherry/Buffer.h>
#include <Cherry/Utils/SDLUtils.hpp>
int main() {

	int r = SDL_Init(SDL_INIT_VIDEO);
	auto wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

	auto settings = std::make_shared<Cherry::RendererSettings>(Cherry::RendererPlatform::OpenGL, true);
	settings->logCallback = [](uint8_t severity, std::string_view msg, std::string_view source) -> void {printf("[LOG %d]\n  %s\n  %s\n", severity, msg.data(), source.data()); };
	
	try {
		auto api = Cherry::RendererAPI::Create(wnd, settings);
		api->Init();
	}
	catch (std::exception e) {
		printf("%s", e.what());
	}
	auto buf = Cherry::VertexBuffer::Create(nullptr, 2, 10);

	glEnable(0);

	return 0;
}