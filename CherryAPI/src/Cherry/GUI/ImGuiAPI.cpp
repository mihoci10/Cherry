#include "ImGuiAPI.h"

#include <Cherry/Utils/Log.hpp>
#include <Cherry/Platform/OpenGL/GUI/OpenGLImGuiAPI.h>

#include "backends/imgui_impl_sdl3.h"

namespace Cherry::GUI {

    ImGuiAPI::ImGuiAPI(std::shared_ptr<RendererAPI> renderer)
        : m_Renderer(renderer)
    {
    }

    void ImGuiAPI::Initialize()
    {
        ImGui::CreateContext();
    }

    void ImGuiAPI::Deinitialize()
    {
        ImGui_ImplSDL3_Shutdown();
    }

    void ImGuiAPI::NewFrame()
    {
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiAPI::DrawFrame()
    {
        ImGui::Render();
    }

    bool ImGuiAPI::OnEvent(const SDL_Event* event)
    {
        return ImGui_ImplSDL3_ProcessEvent(event);
    }

    std::unique_ptr<ImGuiAPI> ImGuiAPI::Create(std::shared_ptr<RendererAPI> renderer)
    {

        switch (renderer->GetRendererSettings().platform)
        {
        case Cherry::RendererPlatform::None:
            CHERRY_THROW("Headless mode is not supported by ImGui API!");
        case Cherry::RendererPlatform::OpenGL:
            return std::make_unique<OpenGLImGuiAPI>(renderer);
        case Cherry::RendererPlatform::Vulkan:
            CHERRY_THROW("Vulcan platform is not supported by ImGui API!");
        }
    }
}