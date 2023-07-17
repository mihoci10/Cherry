#include "OpenGLImGuiAPI.h"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

namespace Cherry::GUI {

	OpenGLImGuiAPI::OpenGLImGuiAPI(std::shared_ptr<RendererAPI> renderer)
		: ImGuiAPI(renderer)
	{
		Initialize();
	}

	OpenGLImGuiAPI::~OpenGLImGuiAPI()
	{
		Deinitialize();
	}

	void OpenGLImGuiAPI::Initialize()
	{
		ImGuiAPI::Initialize();
		ImGui_ImplSDL3_InitForOpenGL(m_Renderer->GetWindowHandle().get(), SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGLImGuiAPI::Deinitialize()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGuiAPI::Deinitialize();
	}

	void OpenGLImGuiAPI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGuiAPI::NewFrame();
	}

	void OpenGLImGuiAPI::DrawFrame()
	{
		ImGuiAPI::DrawFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}