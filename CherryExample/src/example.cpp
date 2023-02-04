#include <GL/glew.h>
#include <SDL.h>
#include <Cherry/RendererAPI.h>
#include <Cherry/RenderContext.h>
#include <Cherry/Utils/SDLUtils.hpp>
int main() {
	auto settings = std::make_shared<Cherry::RendererSettings>(Cherry::RendererPlatform::OpenGL, true);
	auto api = Cherry::RendererAPI::Create(settings);

	int r = SDL_Init(SDL_INIT_VIDEO);
	auto wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

	auto ctx = Cherry::RenderContext::Create(wnd);

	ctx->Init();
	api->Init();

	SDL_DestroyWindow(wnd.get());
	return 0;
}