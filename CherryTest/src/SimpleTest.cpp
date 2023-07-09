#include <gtest/gtest.h>

#include <Cherry/RendererAPI.h>
#include <Cherry/Utils/SDLUtils.hpp>


class RendererAPIFixture : public testing::TestWithParam<std::tuple<Cherry::RendererPlatform, bool>> {
protected:
	RendererAPIFixture() {
		auto [platform, debugMode] = GetParam();

		Settings = std::make_shared<Cherry::RendererSettings>(platform, debugMode);
		Wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

		RendererApi = Cherry::RendererAPI::Create(Wnd, Settings);
	};
	std::unique_ptr<Cherry::RendererAPI> RendererApi;

private:
	std::shared_ptr<Cherry::RendererSettings> Settings;
	std::shared_ptr<SDL_Window> Wnd;
};

TEST_P(RendererAPIFixture, StartStop) {
	RendererApi->Init();
	RendererApi->Deinit();
}

INSTANTIATE_TEST_SUITE_P(
	RendererAPITests,
	RendererAPIFixture,
	testing::Values(
		std::make_tuple(Cherry::RendererPlatform::OpenGL, true),
		std::make_tuple(Cherry::RendererPlatform::OpenGL, false))
);