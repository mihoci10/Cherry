#include <array>
#include <GL/glew.h>
#include <SDL.h>

#include <Cherry/RendererAPI.h>
#include <Cherry/GUI/ImGuiAPI.h>
#include <Cherry/BufferBatch.h>
#include <Cherry/Utils/SDLUtils.hpp>
#include <Cherry/Shader.h>
#include <Cherry/Framebuffer.h>

int main() {

	int r = SDL_InitSubSystem(SDL_INIT_VIDEO);
	auto wnd = std::shared_ptr<SDL_Window>(SDL_CreateWindow("CherryExample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL), Cherry::SDL_Deleter());

	auto settings = Cherry::RendererSettings(Cherry::RendererPlatform::OpenGL, true);
	settings.logCallback = [](uint8_t severity, std::string_view msg, std::string_view source) -> void {printf("[LOG %d]\n  %s\n  %s\n", severity, msg.data(), source.data()); };

	std::shared_ptr<Cherry::RendererAPI> rendererApi;

	try {
		rendererApi = Cherry::RendererAPI::Create(wnd, settings);
	}
	catch (std::exception e) {
		printf("%s", e.what());
		return 1;
	}

	std::unique_ptr<Cherry::GUI::ImGuiAPI> imGuiApi = Cherry::GUI::ImGuiAPI::Create(rendererApi);

	rendererApi->SetViewport(0, 0, 512, 512);
	rendererApi->SetClearColor(glm::vec4(0.5));

	std::array<float, 9> vertices{
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	std::array<uint32_t, 3> indicies{
		0, 1, 2
	};

	auto desc = Cherry::BufferDescriptor();
	desc.AddSegment(Cherry::BufferDataType::FLOAT, 3, false);
	std::shared_ptr<Cherry::VertexBuffer> buf = 
		Cherry::VertexBuffer::Create(rendererApi->GetRendererSettings(), vertices.data(), desc, 3);

	auto indDesc = Cherry::BufferDescriptor();
	indDesc.AddSegment(Cherry::BufferDataType::UINT_32, 1, false);
	std::shared_ptr<Cherry::IndexBuffer> indexBuffer = 
		Cherry::IndexBuffer::Create(rendererApi->GetRendererSettings(), indicies.data(), indDesc, 3);

	auto bufferBatch = Cherry::BufferBatch::Create(rendererApi->GetRendererSettings());
	bufferBatch->AddVertexBuffer(buf);
	bufferBatch->SetIndexBuffer(indexBuffer);

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

	auto shader = Cherry::Shader::Create(rendererApi->GetRendererSettings(), "Basic", vertexShader, fragShader);

	auto framebuffer = Cherry::Framebuffer::Create(rendererApi->GetRendererSettings(), 
		{ 100, 100, 1, {Cherry::FramebufferTextureFormat::Color} });

	SDL_Event ev;
	while (true) {
		while (SDL_PollEvent(&ev) != 0) { imGuiApi->OnEvent(&ev); };

		imGuiApi->NewFrame();
		rendererApi->Clear();

		framebuffer->Resize(500, 500);

		framebuffer->Bind();
		rendererApi->Clear();
		shader->Bind();
		rendererApi->Draw(*bufferBatch.get());
		framebuffer->Unbind();

		// render your GUI
		ImGui::Begin("Demo window");	
		ImGui::Text("asdf");
		ImGui::Image((void*)framebuffer->GetColorAttachmentID(), ImVec2(500,500), ImVec2(1,1), ImVec2(0, 0));
		ImGui::End();

		imGuiApi->DrawFrame();

		SDL_GL_SwapWindow(wnd.get());
	}

	return 0;
}