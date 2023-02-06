#include <GL/glew.h>
#include <SDL.h>
#include <Cherry/RendererAPI.h>
#include <Cherry/Utils/SDLUtils.hpp>
int main() {

	int r = SDL_Init(SDL_INIT_VIDEO);
	auto wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

	auto settings = std::make_shared<Cherry::RendererSettings>(Cherry::RendererPlatform::OpenGL, true);
	settings->logCallback = [](std::string_view msg) -> void {printf("%s\n", msg.data()); };
	auto api = Cherry::RendererAPI::Create(wnd, settings);

	api->Init();
	return 0;
}