#include <array>
#include <GL/glew.h>
#include <SDL.h>

#include <Cherry/RendererAPI.h>
#include <Cherry/GUI/ImGuiAPI.h>
#include <Cherry/Buffer.h>
#include <Cherry/Utils/SDLUtils.hpp>
#include <Cherry/Shader.h>

int main() {

	int r = SDL_Init(SDL_INIT_VIDEO);
	auto wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

	auto settings = std::make_shared<Cherry::RendererSettings>(Cherry::RendererPlatform::OpenGL, true);
	settings->logCallback = [](uint8_t severity, std::string_view msg, std::string_view source) -> void {printf("[LOG %d]\n  %s\n  %s\n", severity, msg.data(), source.data()); };

	std::unique_ptr<Cherry::RendererAPI> api;
	try {
		api = Cherry::RendererAPI::Create(wnd, settings);
		api->Init();
	}
	catch (std::exception e) {
		printf("%s", e.what());
	}

	std::unique_ptr<Cherry::GUI::ImGuiAPI> imGuiApi = Cherry::GUI::ImGuiAPI::Create();
	imGuiApi->Init();

	api->SetViewport(0, 0, 512, 512);
	api->SetClearColor(glm::vec4(0.5));

	std::array<float, 9> vertices{
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	auto desc = std::make_shared<Cherry::BufferDescriptor>();
	desc->AddSegment(Cherry::BufferDataType::FLOAT, 3, false);
	auto buf = Cherry::VertexBuffer::Create(vertices.data(), desc, 3);

	const std::string vertexShader=
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		" }\0";

	const std::string fragShader =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		" }\0";

	auto shader = Cherry::Shader::Create("Basic", vertexShader, fragShader);
	SDL_Event ev;
	while (true) {
		while (SDL_PollEvent(&ev) != 0) {};

		imGuiApi->NewFrame();
		api->Clear();

		shader->Bind();
		buf->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// render your GUI
		ImGui::Begin("Demo window");
		ImGui::Button("Hello!");
		ImGui::End();

		imGuiApi->DrawFrame();

		SDL_GL_SwapWindow(wnd.get());
	}

	return 0;
}