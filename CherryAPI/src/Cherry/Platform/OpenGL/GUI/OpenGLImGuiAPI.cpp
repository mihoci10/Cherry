#include "OpenGLImGuiAPI.h"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"

#include <Cherry/RendererAPI.h>

namespace Cherry::GUI {

	void OpenGLImGuiAPI::Init()
	{
		ImGuiAPI::Init();
		ImGui_ImplSDL3_InitForOpenGL(RendererAPI::GetWindowHnd().get(), SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGLImGuiAPI::Deinit()
	{
		ImGuiAPI::Deinit();
		ImGui_ImplOpenGL3_Shutdown();
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